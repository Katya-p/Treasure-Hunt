#ifndef MATRIX
#define MATRIX
#include "PointWallFunction.h"
#include "Walls.h"

//calculating a distance between two points
double distance(const Point & a, const Point & b);

//check if coord is inside the segment (coord1, coord2) or (coord2, coord1)
bool coordinate_inside_interval(double coord1, double coord2, double coord);

//check if the current interval intersects with any line
bool not_intersects_with_smth(const std::pair <Point, Point> & interval, std::vector<Function> lines);

//comparison of pairs by the first argument
bool compare_pairs(const std::pair<double, Wall> & a, const std::pair<double, Wall> & b);

//sorting std::vector<Wall> walls in ascending order of distance between current_point and middle_point
std::vector<Wall> sorted_by_distance(const std::vector<Wall>  & walls, const Point & current_point);

//checking if all edges around current point are considered
bool all_edges(std::vector<Point> used_points);

//creating an adjacency matrix of a graph consisting of the midpoints of each wall and the treasure
int ** make_matrix(const std::vector<Wall>  & walls, const Point & treasure, const std::vector<Function> & lines);

//deletion of adjacency matrix
void delete_matrix(int ** matrix, size_t size);
#endif