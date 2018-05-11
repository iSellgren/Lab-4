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
#include <unistd.h>


int myrandom (int i)
{
    return std::rand()%i;
}
struct Block{
    
    bool visited =false;
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
    
    labyrinth(int height, int width)
    {
        maze = std::vector <std::vector<Block> >(height, std::vector<Block>(width, Block()));
    }
    

    #define SIZE 19
    std::vector <std::vector<Block>> maze;

};

void print(labyrinth level)
{
    for (auto i = 0; i < SIZE; i++)
    {
        std::cout << std::endl;
        for (auto j = 0; j < SIZE; j++)
            std::cout <<  level.maze[i][j].display;
        
    }
}



void Drill(std::stack<std::pair<int,int>>&back_track,std::stack<std::pair<int,int>>&cur_pos, labyrinth &level,Block)
{

        level.maze[back_track.top().first][back_track.top().second].display = Block::PATH;
        level.maze[back_track.top().first][back_track.top().second].visited = true;
        level.maze[back_track.top().first][back_track.top().second].bot_wall = false;
        
        back_track.push(std::make_pair(back_track.top().first,back_track.top().second));
    
        cur_pos = back_track;
    
}
void Finish(std::stack<std::pair<int,int>>&solve_track,std::stack<std::pair<int,int>>&solve_pos, labyrinth &level,Block)
{

    level.maze[solve_track.top().first][solve_track.top().second].display = Block::F;
    level.maze[solve_track.top().first][solve_track.top().second].visited = true;
    
    solve_track.push(std::make_pair(solve_track.top().first,solve_track.top().second));
    
    solve_pos = solve_track;
    
}



int main() {
    for(int i = 0; i < 2; i++)
    {
    Block block;
    labyrinth level(SIZE, SIZE);
//    Bygg maze
       for(int i=0; i<SIZE; i++) {
            for(int j=0; j<SIZE; j++) {
                level.maze[i][j].display = Block::WALL;
                level.maze[i][j].visited = false;
                level.maze[i][j].top_wall = true;
                level.maze[i][j].bot_wall = true;
                level.maze[i][j].left_wall = true;
                level.maze[i][j].right_wall = true;
            }
        }
        for(int i=1; i<SIZE-1; i++) {
            for(int j=1; j<SIZE-1; j++) {
                level.maze[0][j].top_wall = false;
                level.maze[SIZE-2][j].bot_wall = false;
                level.maze[i][0].left_wall = false;
                level.maze[i][SIZE-2].right_wall = false;
            }
        }
    
    

    std::stack<std::pair<int, int>> back_track;
    std::stack<std::pair<int, int>> solve_track;
    
    level.maze[1][0].display = block.S;
    level.maze[1][1].display = block.START;
    // sätt S som startplats
    back_track.push(std::make_pair(1,1));
    std::stack<std::pair<int, int>> cur_pos = back_track;
    std::stack<std::pair<int, int>> solv_pos = solve_track;
    level.maze[back_track.top().first][back_track.top().second].visited = true;  // Sätt Start som besökt
    srand(unsigned(time(NULL)));
        auto offset = [&](int y, int x)
        {
            return std::make_pair(back_track.top().first + y , (back_track.top().second + x));
        };

//    std::cin.get();
    
    while (!(back_track.empty())) {
        std::vector<std::pair<int ,int>> neighbors;
        

        auto north = offset(-1, 0);
        if(back_track.top().first > 1 && level.maze[north.first][north.second].visited == false)
            if(back_track.top().first > 1 && level.maze[north.first-1][north.second].visited == false && level.maze[north.first][north.second-1].visited == false && level.maze[north.first][north.second+1].visited == false)
            neighbors.push_back(std::make_pair(north.first,north.second));
        

        auto east = offset(0, 1);
        if(back_track.top().second < level.maze.size()-2 && level.maze[east.first][east.second].visited == false)
                  if(back_track.top().second < level.maze.size()-2 && level.maze[east.first][east.second+1].visited == false && level.maze[east.first-1][east.second].visited == false && level.maze[east.first+1][east.second].visited == false)
            neighbors.push_back(std::make_pair(east.first,east.second));
            
        auto west = offset(0,-1);
            if(back_track.top().second > 1 && level.maze[west.first][west.second].visited == false)
                  if(back_track.top().first > 1 && level.maze[west.first][west.second-1].visited == false && level.maze[west.first+1][west.second].visited == false && level.maze[west.first-1][west.second].visited == false)
                neighbors.push_back(std::make_pair(west.first,west.second));
        

        auto south = offset(1,0);
            if(back_track.top().first < level.maze.size()-2 && level.maze[south.first][south.second].visited == false)
                if(back_track.top().first < level.maze.size()-2 && level.maze[south.first+1][south.second].visited == false && level.maze[south.first+1][south.second-1].visited == false && level.maze[south.first][south.second+1].visited == false)
                        neighbors.push_back(std::make_pair(south.first,south.second));
        

        if(neighbors.empty())
        {
            
            //std::cout << " " << std::endl;
            //std::cout << " Popade " << back_track.size() << std::endl;
            if(solve_track.size() < back_track.size())
                solve_track = back_track;
            back_track.pop();
            if(back_track.empty()) break;
            if (level.maze[back_track.top().first][back_track.top().second].visited == false)
            {
                if(back_track.empty()) break;
                back_track.pop();
                
            }
            
            
        
        }
        std::random_shuffle(neighbors.begin(), neighbors.end(), myrandom);
        
        
        
        for (int i = 0; i  < neighbors.size(); i++) {
            back_track.push(neighbors.back());
            neighbors.pop_back();
            
        }

        
        if(back_track.empty()) break;
        
        //std::cout << cur_pos.top().first << "," << cur_pos.top().second << std::endl;
        //std:: cout << back_track.top().first <<"," << back_track.top().second << std::endl;
        
        
        
        
        
        if(back_track.top().first > cur_pos.top().first && back_track.top().second == cur_pos.top().second)
        {
            Drill(back_track, cur_pos, level, block);
        
        }
        if(back_track.top().first == cur_pos.top().first && back_track.top().second > cur_pos.top().second)
        {
            Drill(back_track, cur_pos, level, block);
        }
        
        if(back_track.top().first < cur_pos.top().first && back_track.top().second == cur_pos.top().second)
        {
            Drill(back_track, cur_pos, level, block);
        }
        if(back_track.top().first == cur_pos.top().first && back_track.top().second < cur_pos.top().second)
        {
            Drill(back_track, cur_pos, level, block);
        }
        
        
    }
        if (level.maze[solve_track.top().first][solve_track.top().second].visited == true)
        {
            
            Finish(solve_track, cur_pos, level, block);
            
            
        }
    print(level);

    
    


    
    

    }
     return 0;
}
