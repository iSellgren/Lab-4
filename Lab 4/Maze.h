#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stack>
#include <algorithm>
struct Block {

	bool visited = false;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display = '*';
	static const char WALL = '#';
	static const char PATH = ' ';
	static const char GO = '!';
	static const char S = 'S';
	static  const char F = 'F';
	static const char START = '+';
};

struct labyrinth {

	labyrinth(int height, int width);

	void Generate();
	void Solve_Maze();
	void print();

private:
	std::stack<std::pair<int, int>> back_track;
	void Drill(std::stack<std::pair<int, int>>&back_track, std::stack<std::pair<int, int>>&cur_pos);
	void Finish(std::stack<std::pair<int, int>>&finish_pos, std::stack<std::pair<int, int>>&solve_pos);
	void Solve(std::stack<std::pair<int, int>>&solve_track, std::stack<std::pair<int, int>>&solve_pos);
#define SIZE 14

	std::vector <std::vector<Block>> maze;
	

};
