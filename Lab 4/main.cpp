//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright � 2018 Fredrik Sellgren. All rights reserved.
//
#include "Maze.h"



int main() {
	for (int i = 0; i < 10000000; i++)
	{

  
		labyrinth level(SIZE, SIZE);
        	level.Generate();
        	level.Solve_Maze();
        usleep(100);
        
		
        std::cout << i << std::endl;
	}

	return 0;
}
