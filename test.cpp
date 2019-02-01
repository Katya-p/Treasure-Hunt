#include "pch.h"
#include "../TreasureHunt/Run.h"
//Google testing framework is used
TEST(TestCase, 1) {
	std::vector<std::pair <Point, Point> > input = {
		{{20, 0}, {10, 100}},
		{{40, 0}, {100, 45}},
		{{30, 0}, {95, 100}},
		{{0, 20}, {100, 65}},
		{{85, 0}, {0, 70}},
		{{0, 15}, {65, 100}},
		{{0, 40}, {25, 100}},
		{{55, 100}, {90, 0}},
		{{0, 85}, {100, 90}},
		{{0, 80}, {100, 60}}
	};	
	Point treasure = {48.6, 57.5};
	int res = calculate(input, treasure);
	EXPECT_EQ(res, 3);
}


TEST(TestCase, 2) {
	std::vector<std::pair <Point, Point> > input = {
		{{20, 0}, {10, 100}},
		{{40, 0}, {100, 45}},
		{{30, 0}, {95, 100}},
		{{0, 20}, {100, 65}},
		{{85, 0}, {0, 70}},
		{{0, 15}, {65, 100}},
		{{0, 40}, {25, 100}},
		{{55, 100}, {90, 0}},
		{{0, 85}, {100, 90}},
		{{0, 80}, {100, 60}},
		{{0, 10}, {0, 10}},
		{{30, 100}, {100, 15}},
		{{0, 5}, {100, 50}},
		{{70, 100}, {100, 80}},
		{{0, 30}, {45, 100}}
	};
	Point treasure = { 48.6, 57.5 };
	int res = calculate(input, treasure);
	EXPECT_EQ(res, 4);
}

TEST(TestCase, Empty) {
	std::vector<std::pair <Point, Point> > input;
	Point treasure = { 48.6, 57.5 };
	int res = calculate(input, treasure);
	EXPECT_EQ(res, 1);
}

TEST(TestCase, ExampleInTheTask) {
	std::vector<std::pair <Point, Point> > input = {
		{{20, 0}, {37, 100}},
		{{40, 0}, {76, 100}},
		{{85, 0}, {0, 75}},
		{{100, 90}, {0, 90}},
		{{0, 71}, {100, 61}},
		{{0, 14}, {100, 38}},
		{{100, 47}, {47, 100}}
	};
	Point treasure = { 54.5, 55.4 };
	int res = calculate(input, treasure);
	EXPECT_EQ(res, 2);
}

TEST(TestCase, VerticalHorizontalWalls) {
	std::vector<std::pair <Point, Point> > input = {
		{{10, 0}, {10, 100}},
		{{30, 0}, {30, 100}},
		{{65, 0}, {65, 100}},
		{{80, 0}, {80, 100}},
		{{0, 20}, {100, 20}},
		{{0, 50}, {100, 50}},
		{{0, 85}, {100, 85}},
		{{0, 90}, {100, 90}}

	};
	Point treasure = { 54.5, 55.4 };
	int res = calculate(input, treasure);
	EXPECT_EQ(res, 3);
}