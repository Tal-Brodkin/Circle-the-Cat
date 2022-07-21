#pragma once
#include <vector>
#include "Circle.h"




class Bfs
{
	void run_bfs(std::vector<std::vector<Circle*>>&, Circle*);
	Circle* min_dis_circle(const std::vector<std::vector<Circle*>>&) const;
	Circle* next_circle_to_move(Circle*);

public:

	Bfs() = default;

	void make_neighbors_list(std::vector<std::vector<Circle*>>&);
	Circle* find_shortest_path(std::vector<std::vector<Circle*>>&, Circle*);
};