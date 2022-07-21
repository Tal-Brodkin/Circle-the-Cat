#pragma once

#include "GameManager.h"
#include "Cat.h"
#include "Bfs.h"
#include <string>
#include <list>


class GameWindow
{
	Cat m_cat;

	std::vector<std::vector<Circle*>> m_grid;
	std::list<Circle*> m_previous_clicks;
	std::map<std::string, sf::Text> m_messages;

	sf::Sprite m_reset;
	sf::Sprite m_back;

	int m_clicks_counter;
	int m_level_counter;

	bool m_animation;


	void build_grid();
	void move_cat(sf::RenderWindow&);
	void generate_level(Difficulty);
	void random_circels(const Range&) const;
	void step_back();
	void make_messages();

	sf::Vector2f find_direction();

public:

	GameWindow(const int);
	~GameWindow();

	void press(const sf::Vector2f&, sf::RenderWindow&);
	void handleMouseHover(const sf::Vector2f&) const;
	void draw_screen(sf::RenderWindow&);
	void draw_message_screen(const std::string&, sf::RenderWindow&);

	void reset(const int);
	bool get_animation_status() const;
	void set_animation_status(const bool);
};