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
    clock_t start = clock();
    for(int i = 0; i <2; i++)
    {
        labyrinth level(27, 27);
        level.Generate();
        level.print();
        
    }
    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time it took to complete lab4 sec: %f", elapsed);
    std::cout << std::endl;
    return 0;
    
    
    if(std::string(argv[1]) == "-size")
    {
        if(atoi(argv[2]) > 4)
        {
        int SIZE = atoi(argv[2]);
            labyrinth level(SIZE, SIZE);
            level.Generate();
            level.print();
            std::cout << "Do you wanna export the maze to txt file ? Y / N ";
            
            
            input = std::cin.get();
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
    
    
      return 0;
}

