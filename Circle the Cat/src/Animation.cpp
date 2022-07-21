#include "Animation.h"






Animation::Animation() : m_rect({ 0, 10, 112, 112 })
{
}


void Animation::move_cat(const sf::Vector2f& direction)
{
	auto& directions = GameManager::instance().get_directions_vector();

	if		(directions[UP_LEFT] == direction)		update_top_rect(Row::THIRD, Orientation::REVERSE);
	else if (directions[UP_RIGHT] == direction)		update_top_rect(Row::THIRD);
	else if (directions[LEFT] == direction)			update_top_rect(Row::SECOND, Orientation::REVERSE);
	else if (directions[RIGHT] == direction)		update_top_rect(Row::SECOND);
	else if (directions[DOWN_LEFT] == direction)	update_top_rect(Row::FIRST, Orientation::REVERSE);
	else if (directions[DOWN_RIGHT] == direction)	update_top_rect(Row::FIRST);
	else return;

	updtae_left_rect();
	m_sprite->setTextureRect(m_rect);
}

void Animation::reset()
{
	m_rect = { 0, 10, 112, 112 };
	m_sprite->setScale(1, 1);
	m_sprite->setTextureRect(m_rect);
}

void Animation::set_sprite(sf::Sprite& sprite)
{
	m_sprite = &sprite;
	m_sprite->setTextureRect(m_rect);
}

void Animation::update_top_rect(Row row, Orientation orientation)
{
	m_rect.top = int(row);
	m_sprite->setScale(float(orientation), 1.f);
}

void Animation::updtae_left_rect()
{
	m_rect.left = (m_rect.left + m_rect.width) % (m_rect.width * 9);
}
