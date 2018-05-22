//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright � 2018 Fredrik Sellgren. All rights reserved.
//
#include "Maze.h"



int main(int argc, char** argv) {
    if(atoi(argv[2]) > 4)
    {
    int SIZE = atoi(argv[2]);

  
		labyrinth level(SIZE, SIZE);
        level.Generate();
		level.Solve_Maze();
        system("CLEAR");
        level.print_perfect();
        
        
			

	return 0;
    }else
        std::cerr << "Maze size is to small" << std::endl;
}
