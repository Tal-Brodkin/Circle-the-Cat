#pragma once
#include "GameManager.h"
#include <list>



class Circle
{
	sf::CircleShape m_shape;
	bool m_pressed;
	bool m_visited;
	bool m_edge_circle;
	int m_distance;
	Circle* m_previous;
	std::list<Circle*> m_neighbors;

public:

	Circle(const sf::Vector2f&);

	void edge_circle();
	void nullify_before_bfs();
	void add_neighbor(Circle*);
	void update_previous(Circle*);
	void update_distance(const int);
	void change_fill_color(const sf::Color);
	void change_pressed_status(const bool);
	void change_visited_status(const bool);

	int get_distance() const;

	bool is_pressed() const;
	bool is_edge_circle() const;
	bool is_good_to_move_to() const;
	bool is_clickable(Circle*) const;
	bool is_contain(const sf::Vector2f&) const;

	Circle* get_previous() const;
	sf::CircleShape get_shape() const;
	sf::Vector2f get_visual_position() const;
	const std::list<Circle*>& get_neighbors_list() const;
};