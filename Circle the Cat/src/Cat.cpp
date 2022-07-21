#include "Cat.h"



Cat::Cat() : m_sprite(GameManager::instance().get_texture(CAT))
{
	m_sprite.setOrigin({ 56, 56 });
	m_animation.set_sprite(m_sprite);
}

void Cat::init_bfs(std::vector<std::vector<Circle*>>& grid)
{
	m_bfs.make_neighbors_list(grid);
}

void Cat::find_next_move(std::vector<std::vector<Circle*>>& grid)
{
	if (m_position->is_edge_circle())
	{
		GameManager::instance().level_lost();
		return;
	}

	Circle* next_move = nullptr;
	if (!m_cat_trapped)
		next_move = m_bfs.find_shortest_path(grid, m_position);
	if (next_move == nullptr)
		m_cat_trapped = true;

	if (m_cat_trapped)
	{
		next_move = random_move();
		if (next_move == nullptr)
		{
			GameManager::instance().level_won();
			return;
		}
	}

	m_previous_positions.push_back(m_position);
	m_position = next_move;
}

void Cat::move(const sf::Vector2f& direction)
{
	m_sprite.move(direction);
	m_animation.move_cat(direction);
}

void Cat::set_last_move(const sf::Vector2f& move)
{
	m_last_move = move;
}

void Cat::set_visual_position(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void Cat::set_physical_position(Circle* position) 
{
	m_position = position;
	m_sprite.setPosition(m_position->get_visual_position());
}

void Cat::reset(Circle* starting_circle)
{
	m_cat_trapped = false;
	m_position = starting_circle;
	m_sprite.setPosition(starting_circle->get_visual_position());
	m_previous_positions.clear();
	m_animation.reset();
}

sf::Vector2f Cat::get_last_move() const
{
	return m_last_move;
}

Circle* Cat::random_move() const
{
	auto& posible_moves = m_position->get_neighbors_list();
	
	auto counter = 0;
	for (auto circle : posible_moves)
		if (!circle->is_pressed())
			counter++;

	if (!counter)
		return nullptr;

	auto random_num = 1 + rand() % ((counter + 1) - 1);
	counter = 0;

	for (auto circle : posible_moves)
		if (!circle->is_pressed())
		{
			if (++counter == random_num)
				return circle;
		}

	return nullptr;
}

Circle* Cat::get_position() const
{
	return m_position;
}

std::list<Circle*>& Cat::get_previous_positions()
{ 
	return m_previous_positions;
}

const sf::Sprite& Cat::get_sprite() const
{
	return m_sprite;
}