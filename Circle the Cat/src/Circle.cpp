#include "Circle.h"



Circle::Circle(const sf::Vector2f& position) : m_pressed(false), m_visited(false), m_edge_circle(false), m_distance(0), m_previous(nullptr)
{
	m_shape = sf::CircleShape(CIRCLE_RADIUS);
	m_shape.setFillColor(UNPRESSED);
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
}

void Circle::edge_circle()
{
	m_edge_circle = true;
}

void Circle::change_fill_color(const sf::Color color)
{
	m_shape.setFillColor(color);
}

sf::Vector2f Circle::get_visual_position() const
{
	return m_shape.getPosition();
}

void Circle::change_pressed_status(const bool status)
{
	m_pressed = status;
	if (status)
		change_fill_color(PRESSED);
	else
		change_fill_color(UNPRESSED);
}

void Circle::change_visited_status(const bool status)
{
	m_visited = status;
}

void Circle::add_neighbor(Circle* neighbor)
{
	m_neighbors.push_back(neighbor);
}

void Circle::nullify_before_bfs()
{
	m_visited = false;
	m_distance = 0;
	m_previous = nullptr;
}

void Circle::update_distance(const int distance)
{
	m_distance = distance;
}

void Circle::update_previous(Circle* previous)
{
	m_previous = previous;
}

bool Circle::is_edge_circle() const
{
	return m_edge_circle;
}

bool Circle::is_good_to_move_to() const
{
	return !m_visited && !m_pressed;
}

const std::list<Circle*>& Circle::get_neighbors_list() const
{
	return m_neighbors;
}

sf::CircleShape Circle::get_shape() const
{
	return m_shape;
}

Circle* Circle::get_previous() const
{
	return m_previous;
}

int Circle::get_distance() const
{
	return m_distance;
}

bool Circle::is_clickable(Circle* index) const
{
	return !m_pressed && this != index;
}

bool Circle::is_pressed() const
{
	return m_pressed;
}

bool Circle::is_contain(const sf::Vector2f& position) const
{
	return m_shape.getGlobalBounds().contains(position);
}
