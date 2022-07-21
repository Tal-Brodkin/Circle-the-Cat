#include "Bfs.h"





void Bfs::make_neighbors_list(std::vector<std::vector<Circle*>>& grid)
{
	auto factor = 0;
	auto check = true;

	for (int row = 0; row < grid.size(); row++)
	{
		if (row % 2 == 0)
			factor = 1;
		else
			factor = 0;

		for (int col = 0; col < grid[row].size(); col++)
		{
			if (row != 0 && col != 0 && row != grid.size() - 1 && col != grid[10].size() - 1)
			{
				auto curent_circle = grid[row][col];

				if (check)
				{
					auto& manager = GameManager::instance();
					manager.set_direction(curent_circle, grid[row - 1][col - factor]);
					manager.set_direction(curent_circle, grid[row - 1][col + 1 - factor]);
					manager.set_direction(curent_circle, grid[row][col - 1]);
					manager.set_direction(curent_circle, grid[row][col + 1]);
					manager.set_direction(curent_circle, grid[row + 1][col - factor]);
					manager.set_direction(curent_circle, grid[row + 1][col + 1 - factor]);

					check = false;
				}

				curent_circle->add_neighbor(grid[row - 1][col - factor]);
				curent_circle->add_neighbor(grid[row - 1][col + 1 - factor]);
				curent_circle->add_neighbor(grid[row][col - 1]);
				curent_circle->add_neighbor(grid[row][col + 1]);
				curent_circle->add_neighbor(grid[row + 1][col - factor]);
				curent_circle->add_neighbor(grid[row + 1][col + 1 - factor]);
			}
		}
	}
}

void Bfs::run_bfs(std::vector<std::vector<Circle*>>& grid, Circle* starting_circle)
{
	// Mark all the circles as not visited
	for (auto& row : grid)
		for (auto& col : row)
			col->nullify_before_bfs();

	// Create a queue for BFS
	std::list<Circle*> queue;

	// Mark the current circle as visited and enqueue it
	starting_circle->change_visited_status(true);
	queue.push_back(starting_circle);

	while (!queue.empty())
	{
		// Dequeue a circles from queue
		auto circle = queue.front();
		queue.pop_front();

		// Checks all the neighbors of this circles
		for (auto i : circle->get_neighbors_list())
		{
			// If the neighbor wasn't visited and wasn't pressed
			if (i->is_good_to_move_to())
			{
				i->change_visited_status(true);
				i->update_distance(circle->get_distance() + 1);
				i->update_previous(circle);
				queue.push_back(i);
			}
		}
	}
}

// Finds the minimun distance circle
Circle* Bfs::min_dis_circle(const std::vector<std::vector<Circle*>>& grid) const
{
	int min = INT_MAX;
	Circle* min_dist_circle = nullptr;

	for (auto& row : grid)
		for (auto& col : row)
		{
			if (col->is_edge_circle() && col->get_previous() != nullptr)
				if (col->get_distance() < min)
				{
					min = col->get_distance();
					min_dist_circle = col;
				}
		}
	return min_dist_circle;
}

Circle* Bfs::next_circle_to_move(Circle* min_dist_circle)
{
	if (min_dist_circle == nullptr)
		return nullptr;

	Circle* next_circle_to_move = nullptr;

	while (true)
	{
		if (min_dist_circle->get_previous()->get_previous() != nullptr)
		{
			min_dist_circle = min_dist_circle->get_previous();
		}
		else
		{
			next_circle_to_move = min_dist_circle;
			break;
		}
	}

	return next_circle_to_move;
}

Circle* Bfs::find_shortest_path(std::vector<std::vector<Circle*>>& grid, Circle* starting_circle)
{
	run_bfs(grid, starting_circle);
	auto min_dist_circle = min_dis_circle(grid);
	return next_circle_to_move(min_dist_circle);
}


