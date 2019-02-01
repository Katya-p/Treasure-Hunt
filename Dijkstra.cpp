#include "Dijkstra.h"

int get_result(int ** matrix, size_t size, size_t amount_of_outer_walls)
{
	//Dijkstra's algorithm
	size_t treasure = 0;
	std::vector<int> distance; //vector of  minimal distances between treasure and other vertexes
	std::vector<bool> visited; //vector of visited vertexes
	for (size_t i = 0; i < size; i++)
	{
		distance.push_back(INT_MAX);
		visited.push_back(false);
	}
	distance.at(treasure) = 0;
	size_t index;
	for (size_t count = 0; count < size - 1; count++)
	{
		int min = INT_MAX;
		for (size_t i = 0; i < size; i++) {
			if (!visited.at(i) && distance.at(i) <= min)
			{
				min = distance.at(i);
				index = i;
			}
		}
		visited.at(index) = true;
		for (size_t i = 0; i < size; i++)
			if (!visited.at(i) && matrix[index][i] && distance[index] != INT_MAX && distance[index] + matrix[index][i] < distance.at(i)) {
				distance.at(i) = distance.at(index) + matrix[index][i];
			}
	}

	//finding minimal distance between treasure and midpoints of outer walls
	//it is known that outer vertexes are at the end of vector of walls, amount of outer walls is calculated
	int result = INT_MAX;
	for (size_t i = size - amount_of_outer_walls; i != size; i++) {
		if (distance.at(i) < result) {
			result = distance.at(i);
		}
	}
	return result;
}