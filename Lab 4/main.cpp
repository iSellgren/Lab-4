//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright © 2018 Fredrik Sellgren. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stack>
#include <algorithm>
#include "Maze.h"



int main() {
	for (int i = 0; i < 1000000; i++)
	{
		labyrinth level(SIZE, SIZE);
		//    Bygg maze
		level.Generate();
		level.Solve_Maze();
		
		
	}

	return 0;
}
