#include "Maze.h"
int myrandom(int i)
{
	return std::rand() % i;
}

labyrinth::labyrinth(int height, int width)
{
	maze = std::vector <std::vector<Block> >(height, std::vector<Block>(width, Block()));
}

void labyrinth::Drill(std::stack<std::pair<int, int>>& back_track, std::stack<std::pair<int, int>>& cur_pos)
{
	maze[back_track.top().first][back_track.top().second].display = Block::PATH;
	maze[back_track.top().first][back_track.top().second].visited = true;
	maze[back_track.top().first][back_track.top().second].display = Block::PATH;
	maze[back_track.top().first][back_track.top().second].visited = true;
	maze[back_track.top().first][back_track.top().second].bot_wall = false;

	back_track.push(std::make_pair(back_track.top().first, back_track.top().second));

	cur_pos = back_track;
}
void labyrinth::Finish(std::stack<std::pair<int, int>>&finish_pos, std::stack<std::pair<int, int>>&solve_pos)
{

	maze[finish_pos.top().first][finish_pos.top().second].display = Block::F;
	maze[finish_pos.top().first][finish_pos.top().second].visited = true;

	finish_pos.push(std::make_pair(finish_pos.top().first, finish_pos.top().second));

	finish_pos = finish_pos;

}
void labyrinth::Solve(std::stack<std::pair<int, int>>&solve_track, std::stack<std::pair<int, int>>&solve_pos)
{


	maze[solve_pos.top().first][solve_pos.top().second].display = Block::START;
	maze[solve_pos.top().first][solve_pos.top().second].visited = true;
	if (maze[solve_track.top().first][solve_track.top().second].display == Block::START)
	{
		maze[solve_pos.top().first][solve_pos.top().second].display = Block::S;

	}



	solve_track.push(std::make_pair(solve_track.top().first, solve_track.top().second));
	solve_pos = solve_track;

}


void labyrinth::print()
{
	for (auto i = 0; i < SIZE; i++)
	{
		std::cout << std::endl;
		for (auto j = 0; j < SIZE; j++)
			std::cout << maze[i][j].display;

	}

}
void labyrinth::Generate()
{
	//    Bygg maze
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



	std::stack<std::pair<int, int>> back_track;
	std::stack<std::pair<int, int>> finish_pos;
	std::stack<std::pair<int, int>> finish_track;
	

	maze[1][0].display = Block::S;

	// s�tt S som startplats
	back_track.push(std::make_pair(1, 1));
	finish_track.push(std::make_pair(1, 1));
	std::stack<std::pair<int, int>> cur_pos = back_track;


	maze[back_track.top().first][back_track.top().second].visited = true;  // S�tt Start som bes�kt
	srand(unsigned(time(NULL)));
	auto chk_neib = [&](int y, int x)
	{
		return std::make_pair(back_track.top().first + y, (back_track.top().second + x));
	};


	while (!(back_track.empty()))
	{
		std::vector<std::pair<int, int>> crt_neighbors;


		auto north = chk_neib(-1, 0);
		if (back_track.top().first > 1 && maze[north.first][north.second].visited == false)
			if (back_track.top().first > 1 && maze[north.first - 1][north.second].visited == false && maze[north.first][north.second - 1].visited == false && maze[north.first][north.second + 1].visited == false)
				crt_neighbors.push_back(std::make_pair(north.first, north.second));


		auto east = chk_neib(0, 1);
		if (back_track.top().second < maze.size() - 2 && maze[east.first][east.second].visited == false)
			if (back_track.top().second < maze.size() - 2 && maze[east.first][east.second + 1].visited == false && maze[east.first - 1][east.second].visited == false && maze[east.first + 1][east.second].visited == false)
				crt_neighbors.push_back(std::make_pair(east.first, east.second));

		auto west = chk_neib(0, -1);
		if (back_track.top().second > 1 && maze[west.first][west.second].visited == false)
			if (back_track.top().second > 1 && maze[west.first][west.second - 1].visited == false && maze[west.first + 1][west.second].visited == false && maze[west.first - 1][west.second].visited == false)
				crt_neighbors.push_back(std::make_pair(west.first, west.second));


		auto south = chk_neib(1, 0);
		if (back_track.top().first < maze.size() - 2 && maze[south.first][south.second].visited == false)
			if (back_track.top().first < maze.size() - 2 && maze[south.first + 1][south.second].visited == false && maze[south.first + 1][south.second - 1].visited == false && maze[south.first][south.second + 1].visited == false)
				crt_neighbors.push_back(std::make_pair(south.first, south.second));


		if (crt_neighbors.empty())
		{


			if (finish_pos.size() < back_track.size())
				finish_pos = back_track;
			back_track.pop();
			if (back_track.empty()) break;

			if (maze[back_track.top().first][back_track.top().second].visited == false)
			{

				if (back_track.empty()) 
					break;

				back_track.pop();



			}

		}
		std::random_shuffle(crt_neighbors.begin(), crt_neighbors.end(), myrandom);



		for (size_t i = 0; i < crt_neighbors.size(); i++)
		{
			back_track.push(crt_neighbors.back());
			crt_neighbors.pop_back();

		}


		if (back_track.empty()) break;



		print();
		std::cin.get();

		if (back_track.top().first > cur_pos.top().first && back_track.top().second == cur_pos.top().second)
		{
			Drill(back_track, cur_pos);


		}
		if (back_track.top().first == cur_pos.top().first && back_track.top().second > cur_pos.top().second)
		{
			Drill(back_track, cur_pos);
		}

		if (back_track.top().first < cur_pos.top().first && back_track.top().second == cur_pos.top().second)
		{
			Drill(back_track, cur_pos);
		}
		if (back_track.top().first == cur_pos.top().first && back_track.top().second < cur_pos.top().second)
		{
			Drill(back_track, cur_pos);
		}



	}
	if (maze[finish_pos.top().first][finish_pos.top().second].visited == true)
	{

		Finish(finish_pos, cur_pos);
		maze[1][1].display = Block::START;
	}
}
void labyrinth::Solve_Maze()
{
	
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


		auto north = solve_neib(-1, 0);
		if (solve_track.top().first > 0 && maze[north.first][north.second].display == Block::PATH)
			solve_neighbors.push_back(std::make_pair(north.first, north.second));
		if (solve_track.top().first > 0 && maze[north.first][north.second].display == Block::F)
		{
			maze[north.first + 1][north.second].display = Block::START;
			break;
		}

		auto east = solve_neib(0, 1);
		if (solve_track.top().second < maze.size() && maze[east.first][east.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(east.first, east.second));
		if (solve_track.top().second < maze.size() && maze[east.first][east.second].display == Block::F)
		{
			maze[east.first][east.second - 1].display = Block::START;
			break;
		}

		auto west = solve_neib(0, -1);

		if (solve_track.top().second > 1 && maze[west.first][west.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(west.first, west.second));

		if (solve_track.top().second > 0 && maze[west.first][west.second].display == Block::F)
		{
			maze[west.first][west.second + 1].display = Block::START;
			break;
		}


		auto south = solve_neib(1, 0);
		if (solve_track.top().first < maze.size() - 2 && maze[south.first][south.second].display == Block::PATH)

			solve_neighbors.push_back(std::make_pair(south.first, south.second));
		if (solve_track.top().first < maze.size() && maze[south.first][south.second].display == Block::F)
		{
			maze[south.first - 1][south.second].display = Block::START;
			break;
		}




		if (solve_neighbors.empty())
		{

			solve_track.pop();
			if (maze[solve_pos.top().first][solve_pos.top().second].visited == true)
			{
				solve_track.pop();
				solve_pos.pop();
				if (solve_track.empty())
					return;


			}

			solve_track.pop();

		}


		for (size_t i = 0; i < solve_neighbors.size(); i++)
		{
			solve_track.push(solve_neighbors.back());
			solve_neighbors.pop_back();

		}
		std::random_shuffle(solve_neighbors.begin(), solve_neighbors.end(), myrandom);




		if (solve_track.empty())
			return;

		if (solve_track.top().first > solve_pos.top().first && solve_track.top().second == solve_pos.top().second)
		{
			Solve(solve_track, solve_pos);

		}


		if (solve_track.top().first == solve_pos.top().first && solve_track.top().second > solve_pos.top().second)
		{

			Solve(solve_track, solve_pos);

		}

		if (solve_track.top().first < solve_pos.top().first && solve_track.top().second == solve_pos.top().second)
		{

			Solve(solve_track, solve_pos);

		}
		if (solve_track.top().first == solve_pos.top().first && solve_track.top().second < solve_pos.top().second)
		{

			Solve(solve_track, solve_pos);

		}

	}
}