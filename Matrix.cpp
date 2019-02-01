#include "Matrix.h"

double distance(const Point & a, const Point & b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool coordinate_inside_interval(double coord1, double coord2, double coord)
{
	if (coord1 < coord2) {
		if ((coord > coord1) && (coord < coord2)) {
			return true;
		}
	}
	else if ((coord > coord2) && (coord < coord1)) {
		return true;
	}
	return false;
}

bool not_intersects_with_smth(const std::pair <Point, Point> & interval, std::vector<Function> lines)
{
	for (auto it : lines) {
		Point intersection = calculate_intersection({ calculate_k(interval), calculate_b(interval) }, it);
		//rounding coordinates
		//this is necessary because the calculations with the double type are inaccurate
		double x1 = int(interval.first.x * 1000000) / 1000000.0;
		double x2 = int(interval.second.x * 1000000) / 1000000.0;
		double x = int(intersection.x * 1000000) / 1000000.0;
		double y1 = int(interval.first.y * 1000000) / 1000000.0;
		double y2 = int(interval.second.y * 1000000) / 1000000.0;
		double y = int(intersection.y * 1000000) / 1000000.0;
		//check if intersection point doesn't lie inside interval
		if ((x1 == x2) && coordinate_inside_interval(y1, y2, y)) {
			return false;
		}
		else if (coordinate_inside_interval(x1, x2, x)) {
			return false;
		}
	}
	return true;
}

bool compare_pairs(const std::pair<double, Wall> & a, const std::pair<double, Wall> & b)
{
	return (a.first < b.first);
}

std::vector<Wall> sorted_by_distance(const std::vector<Wall>  & walls, const Point & current_point)
{
	std::vector<std::pair<double, Wall> > pairs;
	for (auto it : walls) {
		pairs.push_back({ distance(it.middle_point, current_point), it });
	}
	std::sort(pairs.begin(), pairs.end(), compare_pairs);
	std::vector<Wall> res;
	for (auto it : pairs) {
		res.push_back(it.second);
	}
	return res;
}

bool all_edges(std::vector<Point> used_points)
{
	if (used_points.empty()) {
		return false;
	}
	//if all edges around current point are considered, all used points are divided into pairs of equal points
	std::sort(used_points.begin(), used_points.end(), compare);
	for (size_t i = 0; i < used_points.size(); i++) {
		if (used_points.at(i) == used_points.at(i + 1)) {
			i++;
		}
		else {
			return false;
		}
	}
	return true;
}

int ** make_matrix(const std::vector<Wall>  & walls, const Point & treasure, const std::vector<Function> & lines)
{
	size_t size = walls.size() + 1;
	int ** matrix = new int *[size];
	for (size_t i = 0; i != size; i++) {
		matrix[i] = new int[size];
	}
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++)
			matrix[i][j] = 0;
	}
	//calculation of the values of paths
	for (size_t i = 0; i < size; i++) {
		Point current_point;
		if (i == 0) {
			//element with index zero is the treasure
			current_point = treasure;
		}
		else {
			current_point = walls.at(i - 1).middle_point;
		}
		std::vector<Wall> distances = sorted_by_distance(walls, current_point);
		std::vector<Point> used_points;
		for (auto it : distances) {
			if (all_edges(used_points)) {
				break;
			}
			if (i == it.index) {
				matrix[i][i] = 0;
				continue;
			}
			if (not_intersects_with_smth({ it.middle_point, current_point }, lines)) {
				matrix[i][it.index] = 1;
				used_points.push_back(it.interval.first);
				used_points.push_back(it.interval.second);
			}
			else {
				matrix[i][it.index] = 0;
			}
			//graph is undirected
			matrix[it.index][i] = matrix[i][it.index];
		}
	}
	return matrix;
}

void delete_matrix(int ** matrix, size_t size) 
{
	for (size_t i = 0; i != size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}