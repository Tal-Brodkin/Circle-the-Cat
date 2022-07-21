#include "GameManager.h"



class Animation
{
	sf::IntRect m_rect;
	sf::Sprite* m_sprite;
	

	void update_top_rect(Row, Orientation orientation = Orientation::NORMAL);
	void updtae_left_rect();

public:

	Animation();

	void move_cat(const sf::Vector2f&);
	void reset();
	void set_sprite(sf::Sprite&);
};