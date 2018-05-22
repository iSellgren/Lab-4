//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright � 2018 Fredrik Sellgren. All rights reserved.
//
#include "Maze.h"



int main(int argc, char** argv) {
    
    if(std::string(argv[1]) == "-size")
    {
        if(atoi(argv[2]) > 4)
        {
        int SIZE = atoi(argv[2]);
            labyrinth level(SIZE, SIZE);
            level.Generate();
//            level.export_maze();
            
        
    
        }else
            std::cerr << "Maze size is to small" << std::endl;
    }
    
    if(std::string(argv[1]) == "-input")
    {
        if(std::string(argv[2]) == "maze.txt")
        {
            int SIZE = 0;
            labyrinth level(SIZE, SIZE);
            level.import_maze();
            level.Solve_Maze();
            level.print_perfect();
            
        }else
            std::cerr << "Maze size is to small" << std::endl;
    }
    
    
    
  /*  labyrinth level(SIZE, SIZE);
    level.import_maze();
    //            level.print();
    //         level.Generate();
    //            level.save_maze();
    level.print();
    //            level.save_maze();
    level.Solve_Maze();
    level.print_perfect();
    //            level.print_perfect();
   */
      return 0;
}

