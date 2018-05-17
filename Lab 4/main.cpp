//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright � 2018 Fredrik Sellgren. All rights reserved.
//
#include "Maze.h"



int main() {
	for (int i = 0; i < 1; i++)
	{

  
		labyrinth level(SIZE, SIZE);
        	level.Generate();
        level.print();
        std::cin.get();
        usleep(1000000);
        	level.Solve_Maze();
        usleep(1000000);
        level.print();
        level.print_perfect();
        usleep(1000000);

        
		
        std::cout << i << std::endl;
	}

	return 0;
}
