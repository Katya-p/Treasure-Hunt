#ifndef WALLS
#define WALLS
#include "PointWallFunction.h"
#include <algorithm>
#include <cmath>

//compare two points
bool compare(const Point & a, const Point & b);

//calculate the midpoint of an interval
Point middle(const Point & a, const Point & b);

//y = kx + b
double calculate_k(const std::pair <Point, Point> & segment);
double calculate_b(const std::pair <Point, Point> & segment);

//calculate the coordinates of the point of intersection of two segments
Point calculate_intersection(const Function &func_a, const Function &func_b);

//creating a vector of k and b defining the linear functions for walls  
std::vector<Function> make_lines(const std::vector<std::pair <Point, Point> > & input);

//creating and adding new walls to a vector of walls
void add_walls(std::vector<Wall> & walls, std::vector<Point> & points, size_t & initial_index);

//the outer walls are the walls that lie on the border of the treasure room
//the outer walls are at the end of the vector of walls, that's why initial index required
//amount of walls should be saved
std::vector<Wall> make_outer_walls(size_t initial_index, const std::vector<std::pair <Point, Point> > & input, size_t & amount_of_walls);

//the inner walls are all the other walls except the outer walls
std::vector<Wall> make_inner_walls(const std::vector<std::pair <Point, Point> > & input, const std::vector<Function> & lines);

//combining inner and outer walls
std::vector<Wall> make_walls(const std::vector<std::pair <Point, Point> > & input,
	size_t & amount_of_outer_walls, const std::vector<Function> & lines);
#endif