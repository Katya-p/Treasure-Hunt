#include "Walls.h"

static const size_t SIZE = 100;

bool compare(const Point & a, const Point & b) {
	bool res = (a.x < b.x);
	if (a.x == b.x) {
		res = (a.y < b.y);
	}
	return res;
}

Point middle(const Point & a, const Point & b) {
	double x = a.x + (b.x - a.x) / 2;
	double y = a.y + (b.y - a.y) / 2;
	return { x, y };
}

double calculate_k(const std::pair <Point, Point> & segment) {
	if (segment.second.x == segment.first.x) {
		return INFINITY;
	}
	return (segment.second.y - segment.first.y) / (segment.second.x - segment.first.x);
}
double calculate_b(const std::pair <Point, Point> & segment) {
	if (segment.second.x == segment.first.x) {
		return INFINITY;
	}
	return (segment.first.y * segment.second.x - segment.second.y * segment.first.x) / (segment.second.x - segment.first.x);
}

Point calculate_intersection(const Function &func_a, const Function &func_b) {
	if (func_b.k == func_a.k) {
		return { INFINITY, INFINITY };
	}
	double x, y;
	if (func_a.k == INFINITY) {
		x = func_a.x0;
		y = x * func_b.k + func_b.b;
	}
	else if (func_b.k == INFINITY) {
		x = func_b.x0;
		y = x * func_a.k + func_a.b;
	}
	else {
		x = (func_a.b - func_b.b) / (func_b.k - func_a.k);
		y = (func_b.k * func_a.b - func_a.k * func_b.b) / (func_b.k - func_a.k);
	}
	return { x, y };
}

std::vector<Function> make_lines(const std::vector<std::pair <Point, Point> > & input) {
	std::vector<Function> lines;
	for (auto it : input) {
		lines.push_back({ calculate_k(it), calculate_b(it), it.first.x });
	}
	return lines;
}

void add_walls(std::vector<Wall> & walls, std::vector<Point> & points, size_t & initial_index) {
	for (size_t i = 0; i < points.size() - 1; i++) {
		Wall tmp = { { points.at(i), points.at(i + 1) },
			middle(points.at(i), (points.at(i + 1))),
			initial_index++
		};
		walls.push_back(tmp);
	}
}

std::vector<Wall> make_outer_walls(size_t initial_index, const std::vector<std::pair <Point, Point> > & input, size_t & amount_of_walls) {
	std::vector<Wall> walls;
	std::vector<Point> points_0_y = { {0, 0}, {0, 100} };
	std::vector<Point> points_100_y = { {100, 0}, {100, 100} };
	std::vector<Point> points_x_0 = { {0, 0}, {100, 0} };
	std::vector<Point> points_x_100 = { {0, 100}, {100, 100} };
	std::vector<Point> all_points;
	for (auto it : input) {
		all_points.push_back(it.first);
		all_points.push_back(it.second);
	}

	for (auto it : all_points) {
		if (it.x == 0) {
			points_0_y.push_back(it);
		}
		if (it.x == 100) {
			points_100_y.push_back(it);
		}
		if (it.y == 0) {
			points_x_0.push_back(it);
		}
		if (it.y == 100) {
			points_x_100.push_back(it);
		}
	}
	std::sort(points_0_y.begin(), points_0_y.end(), compare);
	std::sort(points_100_y.begin(), points_100_y.end(), compare);
	std::sort(points_x_0.begin(), points_x_0.end(), compare);
	std::sort(points_x_100.begin(), points_x_100.end(), compare);

	size_t index = initial_index;
	add_walls(walls, points_0_y, index);
	add_walls(walls, points_100_y, index);
	add_walls(walls, points_x_0, index);
	add_walls(walls, points_x_100, index);
	amount_of_walls = walls.size();
	return walls;
}

std::vector<Wall> make_inner_walls(const std::vector<std::pair <Point, Point> > & input, const std::vector<Function> & lines) {
	std::vector<Wall> walls;
	size_t index = 1;
	for (size_t i = 0; i < lines.size(); i++) {
		Function func = lines.at(i);
		//vector of intersections of current line and all other lines
		std::vector<Point> intersections = { input.at(i).first, input.at(i).second }; 
		for (auto it : lines) {
			Point intersection = calculate_intersection(it, func);
			//if intersection is inside field, it's valid
			if ((intersection.x >= 0) && (intersection.x <= SIZE) && (intersection.y >= 0) && (intersection.y <= SIZE)) {
				intersections.push_back(intersection);
			}
		}
		std::sort(intersections.begin(), intersections.end(), compare);
		add_walls(walls, intersections, index);
	}
	return walls;
}

std::vector<Wall> make_walls(const std::vector<std::pair <Point, Point> > & input,
	size_t & amount_of_outer_walls, const std::vector<Function> & lines) {
	std::vector<Wall> inner_walls = make_inner_walls(input, lines);
	std::vector<Wall> outer_walls = make_outer_walls(inner_walls.size() + 1, input, amount_of_outer_walls);
	for (auto it : outer_walls) {
		inner_walls.push_back(it);
	}
	return inner_walls;
}