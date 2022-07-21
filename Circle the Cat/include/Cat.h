#pragma once
#include <list>
#include "GameManager.h"
#include "Circle.h"
#include "Bfs.h"
#include "Animation.h"

class Cat
{
	Bfs m_bfs;
	sf::Sprite m_sprite;
	Animation m_animation;
	Circle* m_position = nullptr;
	std::list<Circle*> m_previous_positions;
	sf::Vector2f m_last_move;
	bool m_cat_trapped = false;

public:

	Cat();

	void init_bfs(std::vector<std::vector<Circle*>>&);
	void find_next_move(std::vector<std::vector<Circle*>>&);
	void move(const sf::Vector2f&);
	void set_visual_position(const sf::Vector2f&);
	void set_physical_position(Circle*);
	void reset(Circle*);
	void set_last_move(const sf::Vector2f&);

	const sf::Sprite& get_sprite() const;

	sf::Vector2f get_last_move() const;
	Circle* random_move() const;
	Circle* get_position() const;

	std::list<Circle*>& get_previous_positions();
};