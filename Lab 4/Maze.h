//
//  Maze.h
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright � 2018 Fredrik Sellgren. All rights reserved.
//
#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stack>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
struct Block {

	bool visited = false;
	char display = '*';
	static const char WALL = '#';
	static const char PATH = ' ';
	static const char S = 'S';
    static const char W = 'x';
	static  const char F = 'X';
	static const char START = '+';
};

struct labyrinth {

	labyrinth(int height, int width);

	void Generate();
	void Solve_Maze();
	void print();
    void export_maze(std::string(filename));
    void print_perfect();
    bool import_maze(std::string(a));
    

private:
	std::stack<std::pair<int, int>> back_track;
    void Drill(std::stack<std::pair<int, int>>&back_track, std::pair<int, int>&current_position);
	void Finish(std::pair<int, int>&finish_pos);
	void Solve(std::stack<std::pair<int, int>>&solve_track, std::stack<std::pair<int, int>>&solve_pos);

    int SIZE;

	std::vector <std::vector<Block>> maze;
	

};

