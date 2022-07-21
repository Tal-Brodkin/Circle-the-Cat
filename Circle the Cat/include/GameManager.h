#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <vector>
#include <iostream>
#include <string>

class Circle;


class GameManager
{
private:

	std::vector<sf::Vector2f> m_directions;

	bool m_level_won = false;
	bool m_level_lost = false;
	bool m_reset_level = false;

	std::vector<sf::Texture> m_textures;

	sf::Font m_font;

	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:

	static GameManager& instance();
	~GameManager() = default;

	bool is_level_won() const;
	bool is_level_lost() const;
	bool is_level_reset() const;
	void level_won();
	void level_lost();
	void restart_level();
	void reset_level_status();
	void set_direction(const Circle*, const Circle*);

	const sf::Texture& get_texture(const int) const;
	const sf::Font& getFont() const;
	sf::Vector2f get_direction(const Circle*, const Circle*) const;
	const std::vector<sf::Vector2f>& get_directions_vector() const;
};

sf::Vector2f operator/(const sf::Vector2f&, const int);
bool operator!(const sf::Vector2f&);