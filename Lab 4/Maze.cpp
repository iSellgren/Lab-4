#include "Maze.h"

int myrandom(int i)
{
	return std::rand() % i;
}

//S�tter storleken p� labyrinten
labyrinth::labyrinth(int height, int width)
{
	maze = std::vector <std::vector<Block> >(height, std::vector<Block>(width, Block()));
}

// Ta ner v�ggar f�r att fixa v�gar
void labyrinth::Drill(std::stack<std::pair<int, int>>& back_track, std::pair<int, int>& cur_pos)
{
	maze[back_track.top().first][back_track.top().second].display = Block::PATH;
	maze[back_track.top().first][back_track.top().second].visited = true;


	back_track.push(std::make_pair(back_track.top().first, back_track.top().second));

	cur_pos = back_track.top();
}

//S�ttar M�lg�ngen
void labyrinth::Finish(std::stack<std::pair<int, int>>&finish_pos)
{

	maze[finish_pos.top().first][finish_pos.top().second].display = Block::F;
	maze[finish_pos.top().first][finish_pos.top().second].visited = true;

	finish_pos.push(std::make_pair(finish_pos.top().first, finish_pos.top().second));


}
//S�tter l�ser labyrinten
void labyrinth::Solve(std::stack<std::pair<int, int>>&solve_track, std::stack<std::pair<int, int>>&solve_pos)
{


    maze[solve_pos.top().first][solve_pos.top().second].display = Block::START;
    maze[solve_pos.top().first][solve_pos.top().second].visited = true;
        if (maze[solve_track.top().first][solve_track.top().second].display == Block::START)
           {
                    maze[solve_pos.top().first][solve_pos.top().second].display = Block::X;
            
            }
        solve_track.push(std::make_pair(solve_track.top().first, solve_track.top().second));
     solve_pos = solve_track;
    

}

// Skriver ut v�gen som algoritmen tagit
void labyrinth::print()
{
    
	for (auto i = 0; i < SIZE; i++)
	{
		std::cout << std::endl;
		for (auto j = 0; j < SIZE; j++)
        {
            if(maze[i][j].display == Block::X)
                maze[i][j].display = Block::X;
            maze[1][0].display = Block::S;
			std::cout << maze[i][j].display;
        }
            

	}
    

}
// Skriver bara ut den korrekta v�gen till m�let
void labyrinth::print_perfect()
{
    
    for (auto i = 0; i < SIZE; i++)
    {
        std::cout << std::endl;
        for (auto j = 0; j < SIZE; j++)
        {
            if(maze[i][j].display == Block::X)
                maze[i][j].display = Block::PATH;
            maze[1][0].display = Block::S;
            std::cout << maze[i][j].display;
        }
        
        
    }
    
}
void labyrinth::Generate()
{
        clock_t start = clock();
	//    S�tter allt till Walls f�r att sedan kunna bygga mazen
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			maze[i][j].display = Block::WALL;
			maze[i][j].visited = false;
			maze[i][j].top_wall = true;
			maze[i][j].bot_wall = true;
			maze[i][j].left_wall = true;
			maze[i][j].right_wall = true;
		}
	}
	for (int i = 1; i < SIZE - 1; i++) {
		for (int j = 1; j < SIZE - 1; j++) {
			maze[0][j].top_wall = false;
			maze[SIZE - 2][j].bot_wall = false;
			maze[i][0].left_wall = false;
			maze[i][SIZE - 2].right_wall = false;
		}
	}


	//Skapar stackar f�r h�lla koll p� vars man varit och m�let
	std::stack<std::pair<int, int>> back_track;
	std::stack<std::pair<int, int>> finish_pos;
	
	


	// s�tt 1,1 som startplats
	back_track.push(std::make_pair(1, 1));
	// detta f�r att kunna veta vart man ska g�
	std::pair<int, int> cur_pos = back_track.top();


	maze[back_track.top().first][back_track.top().second].visited = true;  // S�tt Start som bes�kt

	// F�r att skapa snabbare srand �n time(NULL).	
	std::string s = "1234567890";
	random_shuffle(s.begin(), s.end());
	std::string g = s.substr(0,4);
	srand(unsigned(time(NULL))+(stoi(g)));
	
	//Funktion till vilka som �r grannar
	auto chk_neib = [&](int y, int x)
	{
		return std::make_pair(back_track.top().first + y, (back_track.top().second + x));
	};


	while (!(back_track.empty()))
	{
		//Skapar en vector med grannar
		std::vector<std::pair<int, int>> crt_neighbors;

		//Kollar om grannen till norr �r ok
		auto north = chk_neib(-1, 0);
		if (back_track.top().first > 1 && maze[north.first][north.second].visited == false)
			if (back_track.top().first > 1 && maze[north.first - 1][north.second].visited == false && maze[north.first][north.second - 1].visited == false && maze[north.first][north.second + 1].visited == false)
				crt_neighbors.push_back(std::make_pair(north.first, north.second));

		//Kollar om grannen till �st �r ok
		auto east = chk_neib(0, 1);
		if (back_track.top().second < maze.size() - 2 && maze[east.first][east.second].visited == false)
			if (back_track.top().second < maze.size() - 2 && maze[east.first][east.second + 1].visited == false && maze[east.first - 1][east.second].visited == false && maze[east.first + 1][east.second].visited == false)
				crt_neighbors.push_back(std::make_pair(east.first, east.second));
		//Kollar om grannen till vest �r ok
		auto west = chk_neib(0, -1);
		if (back_track.top().second > 1 && maze[west.first][west.second].visited == false)
			if (back_track.top().second > 1 && maze[west.first][west.second - 1].visited == false && maze[west.first + 1][west.second].visited == false && maze[west.first - 1][west.second].visited == false)
				crt_neighbors.push_back(std::make_pair(west.first, west.second));

		//Kollar om grannen till s�der �r ok
		auto south = chk_neib(1, 0);
		if (back_track.top().first < maze.size() - 2 && maze[south.first][south.second].visited == false)
			if (back_track.top().first < maze.size() - 2 && maze[south.first + 1][south.second].visited == false && maze[south.first + 1][south.second - 1].visited == false && maze[south.first][south.second + 1].visited == false)
				crt_neighbors.push_back(std::make_pair(south.first, south.second));
		
		//Om det inte finns n�gra grannar
		if (crt_neighbors.empty())
		{

			// S�tt m�let 
			if (finish_pos.size() < back_track.size())
				finish_pos = back_track;

			//poppa fr�n stacken. vi vill hitta tillbaka d�r vi har en granne.
			back_track.pop();
			
			// Om stacken �r tom bryt loopen och f�rs�k hitta nya grannar			
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


		// Stoppa in grannarna i stacken och tabort dem fr�n vectorn
		for (size_t i = 0; i < crt_neighbors.size(); i++)
		{
			back_track.push(crt_neighbors.back());
			crt_neighbors.pop_back();

		}


		



			//G�r en v�g norrut
		if (back_track.top().first > cur_pos.first && back_track.top().second == cur_pos.second)
		{
			Drill(back_track, cur_pos);


		}
			//G�r en v�g �ster
		if (back_track.top().first == cur_pos.first && back_track.top().second > cur_pos.second)
		{
			Drill(back_track, cur_pos);
		}
			//G�r en v�g s�derut
		if (back_track.top().first < cur_pos.first && back_track.top().second == cur_pos.second)
		{
			Drill(back_track, cur_pos);
		}
//            G�r en v�g v�ster
		if (back_track.top().first == cur_pos.first && back_track.top().second < cur_pos.second)
		{
			Drill(back_track, cur_pos);
		}



	}
		// s�tt m�lg�ngen
	if (maze[finish_pos.top().first][finish_pos.top().second].visited == true)
	{

		Finish(finish_pos);
		maze[1][1].display = Block::START;
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

				
		//Kollar om v�gen norrut �r ok
		auto north = solve_neib(-1, 0);
		if (solve_track.top().first > 0 && maze[north.first][north.second].display == Block::PATH)
			solve_neighbors.push_back(std::make_pair(north.first, north.second));
		if (solve_track.top().first > 0 && maze[north.first][north.second].display == Block::F)
		{
			maze[north.first + 1][north.second].display = Block::START;
            std::cout << "DONE"<< std::endl;
            break;
            
        }
		//Kollar om v�gen �sterut �r ok
		auto east = solve_neib(0, 1);
		if (solve_track.top().second < maze.size() && maze[east.first][east.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(east.first, east.second));
		if (solve_track.top().second < maze.size() && maze[east.first][east.second].display == Block::F)
		{
			maze[east.first][east.second - 1].display = Block::START;
		        std::cout << "DONE"<< std::endl;
		        break;
		}

		//Kollar om v�gen v�sterut �r ok
		auto west = solve_neib(0, -1);

		if (solve_track.top().second > 1 && maze[west.first][west.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(west.first, west.second));

		if (solve_track.top().second > 0 && maze[west.first][west.second].display == Block::F)
		{
			maze[west.first][west.second + 1].display = Block::START;
      	 		std::cout << "DONE"<< std::endl;
           		break;
		}

		//Kollar om v�gen s�derut �r ok
		auto south = solve_neib(1, 0);
		if (solve_track.top().first < maze.size() - 2 && maze[south.first][south.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(south.first, south.second));
		if (solve_track.top().first < maze.size() && maze[south.first][south.second].display == Block::F)
		{
			maze[south.first - 1][south.second].display = Block::START;
          		std::cout << "DONE"<< std::endl;
            		break;
		}



		//Om det inte finns n�gra grannar
		if (solve_neighbors.empty())
		{

			solve_track.pop();
		
			// Om vi redan varit d�r vi popade popa igen.
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

   

			// K�r l�sningen
			Solve(solve_track, solve_pos);
	}
    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("Time it took to complete the maze in sec: %f", elapsed);
    std::cout << std::endl;
}
