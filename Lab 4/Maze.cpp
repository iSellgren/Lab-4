//
//  main.cpp
//  Lab 4
//
//  Created by Fredrik Sellgren on 2018-05-07.
//  Copyright 2018 Fredrik Sellgren. All rights reserved.
//
#include "Maze.h"

int myrandom(int i)
{
	return std::rand() % i;
}

//Sätter storleken på labyrinten
labyrinth::labyrinth(int height, int width)
{
    SIZE = height;
    SIZE = width;
	maze = std::vector <std::vector<Block> >(height, std::vector<Block>(width, Block()));
}

// Ta ner vaggar for att fixa gangar
void labyrinth::Drill(std::stack<std::pair<int, int>>& back_track, std::pair<int, int>& current_position)
{
	maze[back_track.top().first][back_track.top().second].display = Block::PATH;
	maze[back_track.top().first][back_track.top().second].visited = true;


	back_track.push(std::make_pair(back_track.top().first, back_track.top().second));

	current_position = back_track.top();
}

//Satter Malgangen
void labyrinth::Finish(std::pair<int, int>&finish_pos)
{

	maze[finish_pos.first][finish_pos.second+1].display = Block::F;
	maze[finish_pos.first][finish_pos.second].visited = true;



}
//Lšser labyrinten
void labyrinth::Solve(std::stack<std::pair<int, int>>&solve_track, std::stack<std::pair<int, int>>&solve_pos)
{


    maze[solve_pos.top().first][solve_pos.top().second].display = Block::START;
    maze[solve_track.top().first][solve_track.top().second].visited = true;
        if (maze[solve_pos.top().first][solve_pos.top().second].display == Block::START)
           {
                    maze[solve_track.top().first][solve_track.top().second].display = Block::W;
            
            }
        solve_track.push(std::make_pair(solve_track.top().first, solve_track.top().second));

    

}

// Skriver ut vad mazen
void labyrinth::print()
{
    std::string test = "";
    
	for (auto i = 0; i < SIZE; i++)
	{
		for (auto j = 0; j < SIZE; j++)
        {
            
			test += maze[i][j].display;
        }
        test += '\n';
	}
    std::cout << test;
}

// exporterar mazen till angivet filnamn.txt
void labyrinth::export_maze(std::string filename)
{
    
    std::ofstream myfile;
    // šppnar en .txt fil med filnamet anvŠdaren uppgivit
    myfile.open(filename+".txt");
    
    for (auto i = 0; i < SIZE; i++)
    {
        for (auto j = 0; j < SIZE; j++)
        {
            maze[1][0].display = Block::S;
            myfile << maze[i][j].display;
            
        }
        myfile << std::endl;;
    }
    myfile.close();
    
    std::cout << "Maze completely exported to " << filename+".txt" << std::endl;
    
}

// Skriver bara ut den korrekta vägen till målet
void labyrinth::print_perfect()
{
    std::string test1 = "";
    
    for (auto i = 0; i < SIZE; i++)
    {
        for (auto j = 0; j < SIZE; j++)
        {
            if(maze[i][j].display == Block::W)
                maze[i][j].display = Block::PATH;
            maze[1][0].display = Block::S;
            test1 += maze[i][j].display;
        }
        test1 += '\n';
    }
    std::cout << test1;
}

//importerar en maze.
bool labyrinth::import_maze(std::string(a))
{
    
    maze.clear();
    char chars;
    int size = 0;
    std::ifstream file(a);
    
    if(file)
    {
        if(file.is_open())
        {
            std::vector<Block> row;
            
            while (!file.eof())
            {
                
                chars = file.get();
                if(chars == Block::PATH)
                {
                    Block Path;
                    Path.display = Block::PATH;
                    row.push_back(Path);
                    
            
                }else if(chars == '\n')
                {
                    SIZE = size-1;
                    maze.push_back(row);
                    row.clear();
                    size = 0;
                }else
                {
                    Block block;
                    block.display = chars;
                    row.push_back(block);
                }
                size++;
            }

            file.close();
            return true;
        }
    }return false;
}
void labyrinth::Generate()
{
        clock_t start = clock();
	//    Sätter allt till Walls för att sedan kunna bygga mazen
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			maze[i][j].display = Block::WALL;
			maze[i][j].visited = false;

		}
	}



	//Skapar stackar för hålla koll på vars man varit och målet
	std::stack<std::pair<int, int>> back_track;
	std::pair<int, int> finish_pos;
	
	


	// sätt 1,1 som startplats
	back_track.push(std::make_pair(1, 1));
	// detta för att kunna veta vart man ska gå
	std::pair<int, int> current_position = back_track.top();


	maze[back_track.top().first][back_track.top().second].visited = true;  // Sätt Start som besökt

	// För att skapa snabbare srand än time(NULL).	
	std::string s = "1234567890";
	random_shuffle(s.begin(), s.end());
	std::string g = s.substr(0,4);
	srand(unsigned(time(NULL))+(stoi(g)));
	
	//Funktion till vilka som är grannar
	auto chk_neib = [&](int y, int x)
	{
		return std::make_pair(back_track.top().first + y, (back_track.top().second + x));
	};


	while (!(back_track.empty()))
	{
		//Skapar en vector med grannar
		std::vector<std::pair<int, int>> crt_neighbors;

		//Kollar om grannen till norr är ok
		auto north = chk_neib(-1, 0);
		if (back_track.top().first > 1 && maze[north.first][north.second].visited == false)
			if (back_track.top().first > 1 && maze[north.first - 1][north.second].visited == false && maze[north.first][north.second - 1].visited == false && maze[north.first][north.second + 1].visited == false)
				crt_neighbors.push_back(std::make_pair(north.first, north.second));

		//Kollar om grannen till öst är ok
		auto east = chk_neib(0, 1);
		if (back_track.top().second < maze.size() - 2 && maze[east.first][east.second].visited == false)
			if (back_track.top().second < maze.size() - 2 && maze[east.first][east.second + 1].visited == false && maze[east.first - 1][east.second].visited == false && maze[east.first + 1][east.second].visited == false)
				crt_neighbors.push_back(std::make_pair(east.first, east.second));
		//Kollar om grannen till vest är ok
		auto west = chk_neib(0, -1);
		if (back_track.top().second > 1 && maze[west.first][west.second].visited == false)
			if (back_track.top().second > 1 && maze[west.first][west.second - 1].visited == false && maze[west.first + 1][west.second].visited == false && maze[west.first - 1][west.second].visited == false)
				crt_neighbors.push_back(std::make_pair(west.first, west.second));

		//Kollar om grannen till söder är ok
		auto south = chk_neib(1, 0);
		if (back_track.top().first < maze.size() - 2 && maze[south.first][south.second].visited == false)
			if (back_track.top().first < maze.size() - 2 && maze[south.first + 1][south.second].visited == false && maze[south.first + 1][south.second - 1].visited == false && maze[south.first][south.second + 1].visited == false)
				crt_neighbors.push_back(std::make_pair(south.first, south.second));
		
		//Om det inte finns några grannar
		if (crt_neighbors.empty())
		{

			// Sätt målet 
			if (finish_pos < back_track.top())
				finish_pos = back_track.top();

			//poppa från stacken. vi vill hitta tillbaka där vi har en granne.
			back_track.pop();
			
			// Om stacken är tom bryt loopen och försök hitta nya grannar			
			if (back_track.empty()) 
				break;

			if (maze[back_track.top().first][back_track.top().second].visited == false)
			{

				if (back_track.empty()) 
					break;

				back_track.pop();



			}

		}
			//Shufflea om de giltiga grannarna
		std::random_shuffle(crt_neighbors.begin(), crt_neighbors.end(), myrandom);


		// Stoppa in grannarna i stacken och tabort dem från vectorn
		for (size_t i = 0; i < crt_neighbors.size(); i++)
		{
			back_track.push(crt_neighbors.back());
			crt_neighbors.pop_back();

		}


		



			//Gör en väg norrut
		if (back_track.top().first > current_position.first && back_track.top().second == current_position.second)
		{
			Drill(back_track, current_position);


		}
			//Gör en väg öster
		if (back_track.top().first == current_position.first && back_track.top().second > current_position.second)
		{
			Drill(back_track, current_position);
		}
			//Gör en väg söderut
		if (back_track.top().first < current_position.first && back_track.top().second == current_position.second)
		{
			Drill(back_track, current_position);
		}
//            Gör en väg väster
		if (back_track.top().first == current_position.first && back_track.top().second < current_position.second)
		{
			Drill(back_track, current_position);
		}

	}
		// sätt målgången
	if (maze[finish_pos.first][finish_pos.second].visited == true)
	{

		Finish(finish_pos);
		maze[1][1].display = Block::START;
        maze[1][0].display = Block::S;
	}

    
    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time it took to build maze in sec: %f", elapsed);
    std::cout << std::endl;
}
void labyrinth::Solve_Maze()
{
   clock_t start = clock();
	
	std::stack<std::pair<int, int>> solve_track;
	solve_track.push(std::make_pair(1, 1));
	std::stack<std::pair<int, int>> solve_pos = solve_track;

	
	auto solve_neib = [&](int y, int x)
	{
		return std::make_pair(solve_track.top().first + y, (solve_track.top().second + x));
	};
	while (!(solve_track.empty()))
	{
		std::vector<std::pair<int, int>> solve_neighbors;

		
		//Kollar om vägen norrut är ok
		auto north = solve_neib(-1, 0);
		if (solve_track.top().first > 0 && maze[north.first][north.second].display == Block::PATH)
			solve_neighbors.push_back(std::make_pair(north.first, north.second));
		if (solve_track.top().first > 0 && maze[north.first][north.second].display == Block::F)
		{
			maze[north.first + 1][north.second].display = Block::START;
            std::cout << "DONE"<< std::endl;
            break;
            
        }
		//Kollar om vägen österut är ok
		auto east = solve_neib(0, 1);
		if (solve_track.top().second < maze.size() && maze[east.first][east.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(east.first, east.second));
		if (solve_track.top().second < maze.size() && maze[east.first][east.second].display == Block::F)
		{
			maze[east.first][east.second - 1].display = Block::START;
		        std::cout << "DONE"<< std::endl;
		        break;
		}

		//Kollar om vägen västerut är ok
		auto west = solve_neib(0, -1);

		if (solve_track.top().second > 1 && maze[west.first][west.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(west.first, west.second));

		if (solve_track.top().second > 0 && maze[west.first][west.second].display == Block::F)
		{
			maze[west.first][west.second + 1].display = Block::START;
      	 		std::cout << "DONE"<< std::endl;
           		break;
		}

		//Kollar om vägen söderut är ok
		auto south = solve_neib(1, 0);
		if (solve_track.top().first < maze.size() - 2 && maze[south.first][south.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(south.first, south.second));
		if (solve_track.top().first < maze.size() && maze[south.first][south.second].display == Block::F)
		{
			maze[south.first - 1][south.second].display = Block::START;
          		std::cout << "DONE"<< std::endl;
            		break;
		}



		//Om det inte finns några grannar
		if (solve_neighbors.empty())
		{

			solve_track.pop();
		
			// Om vi redan varit där vi popade popa igen.
			if (maze[solve_pos.top().first][solve_pos.top().second].visited == true)
			{
                
				solve_track.pop();
                		solve_pos.pop();
				
				if (solve_track.empty())
                		{
                		    std::cin.get();
                		    break;
                		}
	
			}

			
		}

		//Stoppa in de gilltiga grannarna i stacken och popa vectorn
		for (size_t i = 0; i < solve_neighbors.size(); i++)
		{
			solve_track.push(solve_neighbors.back());
			solve_neighbors.pop_back();

		}
		//Kasta om grannarna i vectorn
		std::random_shuffle(solve_neighbors.begin(), solve_neighbors.end(), myrandom);

   
		
			// Kör lösningen
			Solve(solve_track, solve_pos);
			solve_pos.push(std::make_pair(solve_track.top().first, solve_track.top().second));
	}
    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time it took to complete the maze in sec: %f", elapsed);
    std::cout << std::endl;

}
