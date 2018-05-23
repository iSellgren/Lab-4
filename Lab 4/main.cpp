//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright � 2018 Fredrik Sellgren. All rights reserved.
//
#include "Maze.h"



int main(int argc, char** argv) {
    std::string input = "";
    std::string filename ="";
    
    
    if(std::string(argv[1]) == "-size")
    {
        if(atoi(argv[2]) > 4)
        {
        int SIZE = atoi(argv[2]);
            labyrinth level(SIZE, SIZE);
            level.Generate();
            std::cout << "Do you wanna export the maze ? Y / N ";
            
            std::cin >> input;
            if(input == "Y")
            {
                std::cout << "Please enter file name ";
                std::cin >> filename;
                level.export_maze(filename);
                
            }
        }else
            std::cerr << "Maze size is to small" << std::endl;
        

        
    }
    
    else if(std::string(argv[1]) == "-input")
    {
        
            int SIZE = 0;
            labyrinth level(SIZE, SIZE);
            if(level.import_maze(std::string(argv[2])))
            {
                level.Solve_Maze();
                level.print_perfect();
            }else
                std::cerr << "Cant open file ";
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

