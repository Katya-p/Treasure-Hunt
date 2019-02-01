#ifndef RUN
#define RUN
#include "Dijkstra.h"
#include <iostream>

//calculate the minimum number of doors
int calculate(const std::vector<std::pair <Point, Point> > & input, const Point &treasure);

//input, output and calculating the minimum number of doors
void run();

#endif