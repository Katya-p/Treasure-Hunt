#include "Run.h"

int calculate(const std::vector<std::pair <Point, Point> > & input, const Point &treasure)
{
	size_t amount_of_outer_walls;
	std::vector<Function> lines = make_lines(input);
	std::vector<Wall> walls = make_walls(input, amount_of_outer_walls, lines);
	int ** ptr = make_matrix(walls, treasure, lines); //creating adjacency matrix
	int result = get_result(ptr, walls.size() + 1, amount_of_outer_walls); 	//calculating result 
	delete_matrix(ptr, walls.size() + 1); 	//deleting adjacency matrix
	return result;
}

void run()
{
	//data input
	int amount_of_lines;
	std::cin >> amount_of_lines;
	std::vector<std::pair <Point, Point> > input;
	for (int i = 0; i < amount_of_lines; i++) {
		double first_x;
		double first_y;
		double second_x;
		double second_y;
		std::cin >> first_x >> first_y >> second_x >> second_y;
		input.push_back({ { first_x, first_y }, { second_x, second_y} });
	}
	double treasure_x;
	double treasure_y;
	std::cin >> treasure_x >> treasure_y;
	Point treasure = { treasure_x, treasure_y };
	int result = calculate(input, treasure); 	//calculating
	std::cout << "Number of doors = " << result << std::endl; 	//data output
}