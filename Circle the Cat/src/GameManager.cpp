#include "GameManager.h"
#include "Circle.h"


GameManager::GameManager()
{
    auto texture = sf::Texture();
    texture.loadFromFile("cat.png");
    m_textures.push_back(texture);
    texture.loadFromFile("reset.png");
    m_textures.push_back(texture);
    texture.loadFromFile("back.png");
    m_textures.push_back(texture);

    m_font.loadFromFile("Raleway.ttf");
}

GameManager& GameManager::instance()
{
    static GameManager instance;
    return instance;
}

bool GameManager::is_level_won() const
{
    return m_level_won;
}

bool GameManager::is_level_lost() const
{
    return m_level_lost;
}

bool GameManager::is_level_reset() const
{
    return m_reset_level;
}

void GameManager::level_won()
{
    m_level_won = true;
}

void GameManager::level_lost()
{
    m_level_lost = true;
}

void GameManager::restart_level()
{
    m_reset_level = true;
}

void GameManager::reset_level_status()
{
    m_level_won = false;
    m_level_lost = false;
    m_reset_level = false;
}

void GameManager::set_direction(const Circle* origin, const Circle* dest)
{
    m_directions.push_back(get_direction(origin, dest));
}

const sf::Texture& GameManager::get_texture(const int index) const
{
    return m_textures[index];
}

const sf::Font& GameManager::getFont() const
{
    return m_font;
}

sf::Vector2f GameManager::get_direction(const Circle* origin, const Circle* dest) const
{
    return (dest->get_shape().getPosition() - origin->get_shape().getPosition()) / FRAMES;
}

const std::vector<sf::Vector2f>& GameManager::get_directions_vector() const
{
    return m_directions;
}

sf::Vector2f operator/(const sf::Vector2f& vec, const int factor)
{
    return sf::Vector2f(vec.x / factor, vec.y / factor);
}

bool operator!(const sf::Vector2f& vec)
{
    return vec.x == 0 && vec.y == 0;
}
