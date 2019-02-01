#ifndef POINTWALLFUNCTION
#define POINTWALLFUNCTION
#include <vector>

//coordinates of point 
struct Point {
	double x;
	double y;	

	bool operator==(const Point & other) {
		return ((x == other.x) && (y == other.y));
	}

	bool operator!=(const Point & other) {
		return !(*this == other);
	}
};

//y = kx + b
struct Function {
	double k;
	double b;
	double x0; //intersection with axis x (only for infinite k)
};

struct Wall {
	std::pair<Point, Point> interval; //coordinates of edges of a wall
	Point middle_point; //coordinates of a middle point
	size_t index; //index of a wall

	bool operator==(const Wall & other) {
		return (interval.first == other.interval.first) && (interval.second == other.interval.second);
	}

	bool operator!=(const Wall & other) {
		return !(*this == other);
	}
};

#endif
