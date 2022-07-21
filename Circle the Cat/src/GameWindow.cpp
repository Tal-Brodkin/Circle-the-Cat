#include "GameWindow.h"



GameWindow::GameWindow(const int level) : m_clicks_counter(0), m_level_counter(level + 1), m_animation(false)
{
	GameManager::instance().reset_level_status();

	build_grid();
	generate_level(Difficulty(level));
	make_messages();

	m_cat.set_physical_position(m_grid[START][START]);
	m_cat.init_bfs(m_grid);
	m_reset.setTexture(GameManager::instance().get_texture(RESET));
	m_back.setTexture(GameManager::instance().get_texture(BACK));
	m_reset.setPosition(700, 700);
	m_back.setPosition(50, 700);
}

GameWindow::~GameWindow()
{
	for (auto& row : m_grid)
		for (auto col : row)
			delete col;
}

void GameWindow::build_grid()
{
	float x;

	for (int row = 1; row < 12; row++)
	{
		auto temp = std::vector<Circle*>();
		for (int col = 1; col < 12; col++)
		{
			row % 2 == 0 ? x = float(col + 0.5) : x = float(col);
			auto position = sf::Vector2f(float(x * 65), float(row * 55));
			auto circle = new Circle(position);
			if (row == 1 || col == 1 || row == 11 || col == 11)
				circle->edge_circle();
			temp.push_back(circle);
		}
		m_grid.push_back(temp);
	}
}

void GameWindow::generate_level(Difficulty difficulty)
{
	switch (difficulty)
	{
		case Difficulty::EASY:		random_circels(HIGH);		break;
		case Difficulty::MEDIUM:	random_circels(NORMAL);		break;
		case Difficulty::HARD:		random_circels(LOW);		break;
		case Difficulty::EXTREME:	random_circels(VERY_LOW);	break;

		default:					random_circels(VERY_LOW);	break;
	}
}

void GameWindow::random_circels(const Range& range) const
{
	auto random_num = range.min + rand() % ((range.max + 1) - range.min);
	auto bad_numbers = true;
	auto x = 0, y = 0;

	while (random_num)
	{
		while (bad_numbers)
		{
			x = rand() % (11);
			y = rand() % (11);
			if (x != 5 || y != 5)
				bad_numbers = false;
		}

		m_grid[x][y]->change_pressed_status(true);

		random_num--;
		bad_numbers = true;
	}
}

void GameWindow::press(const sf::Vector2f& position, sf::RenderWindow& window) 
{
	if (m_animation)
		return;

	for (auto& row : m_grid)
		for (auto& circle : row)
			if (circle->is_contain(position))
			{
				if (circle->is_clickable(m_cat.get_position()))
				{
					circle->change_pressed_status(true);

					m_previous_clicks.push_back(circle);
					m_clicks_counter++;
					m_messages["clicks"].setString("Clicks: " + std::to_string(m_clicks_counter));

					move_cat(window);
				}
				return;
			}

	if (m_reset.getGlobalBounds().contains(position))
		GameManager::instance().restart_level();

	if (m_back.getGlobalBounds().contains(position))
	{
		step_back();
	}
}


void GameWindow::move_cat(sf::RenderWindow& window) 
{
	m_animation = true;

	auto direction = find_direction();

	for (auto frame = 0; frame < FRAMES * FACTOR; frame++)
	{
		window.clear(sf::Color::White);
		if (frame % FACTOR == 0)
			m_cat.move(direction);

		draw_screen(window);
		window.display();
	}

	m_cat.set_last_move(direction);
}

sf::Vector2f GameWindow::find_direction()
{
	auto origin = m_cat.get_position();
	m_cat.find_next_move(m_grid);
	auto dest = m_cat.get_position();
	auto direction = GameManager::instance().get_direction(origin, dest);


	if (!direction && m_cat.get_position()->is_edge_circle())
	{
		auto& directions = GameManager::instance().get_directions_vector();

		if (m_cat.get_sprite().getPosition().x < 100)
			return directions[LEFT];
		if (m_cat.get_sprite().getPosition().x > 700)
			return directions[RIGHT];
		if (m_cat.get_sprite().getPosition().y < 100)
			return directions[UP_LEFT];
		if (m_cat.get_sprite().getPosition().y > 600)
			return directions[DOWN_LEFT];
	}

	return direction;
}

void GameWindow::step_back() 
{
	auto& posiotns = m_cat.get_previous_positions();

	if (posiotns.size() == 0)
		return;

	m_clicks_counter--;
	m_messages["clicks"].setString("Clicks: " + std::to_string(m_clicks_counter));

	auto previous_position = posiotns.back();
	posiotns.pop_back();
	m_cat.set_visual_position(previous_position->get_visual_position());
	m_cat.set_physical_position(previous_position);

	auto privious_click = m_previous_clicks.back();
	m_previous_clicks.pop_back();
	privious_click->change_pressed_status(false);
	privious_click->change_fill_color(UNPRESSED);
}

void GameWindow::handleMouseHover(const sf::Vector2f& position) const
{
	for (auto& row : m_grid)
		for (auto& circle : row)
		{
			if (circle->is_contain(position))
			{
				if (circle->is_clickable(m_cat.get_position()))
					circle->change_fill_color(HOVER);
			}
			else
			{
				if (!circle->is_pressed())
					circle->change_fill_color(UNPRESSED);
			}
		}
}

void GameWindow::draw_screen(sf::RenderWindow& window)
{
	for (auto& row : m_grid)
		for (auto& circle : row)
			window.draw(circle->get_shape());

	window.draw((m_cat.get_sprite()));
	window.draw(m_back);
	window.draw(m_reset);
	window.draw(m_messages[CLICKS]);
	window.draw(m_messages[LEVEL]);
}

void GameWindow::draw_message_screen(const std::string& type, sf::RenderWindow& window) 
{
	window.draw(m_messages[type]);
	window.draw(m_messages[CONTINUE]);
	window.draw(m_back);
	window.draw(m_reset);
	window.draw(m_messages[CLICKS]);
	window.draw(m_messages[LEVEL]);
}

void GameWindow::reset(const int level)
{
	GameManager::instance().reset_level_status();

	for (auto& row : m_grid)
		for (auto col : row)
			col->change_pressed_status(false);

	generate_level(Difficulty(level));
	m_clicks_counter = 0;
	m_level_counter = level + 1;
	m_messages[CLICKS].setString("Clicks: " + std::to_string(m_clicks_counter));
	m_messages[LEVEL].setString("Level: " + std::to_string(m_level_counter));
	m_cat.reset(m_grid[START][START]);
}

bool GameWindow::get_animation_status() const
{
	return m_animation;
}

void GameWindow::set_animation_status(const bool status)
{
	m_animation = status;
}

void GameWindow::make_messages()
{
	std::string clicks_counter = std::to_string(m_clicks_counter);
	std::string level_counter = std::to_string(m_level_counter);

	auto& font = GameManager::instance().getFont();

	sf::Text win_message;
	win_message.setFont(font);
	win_message.setString("WELL DONE, YOU CAUGHT THE CAT");
	win_message.setCharacterSize(30);
	win_message.setFillColor(sf::Color(255, 61, 57));
	win_message.setPosition(150, 350);

	sf::Text lose_message;
	lose_message.setFont(font);
	lose_message.setString("THE CAT RAN AWAY, TRY AGAIN");
	lose_message.setCharacterSize(30);
	lose_message.setFillColor(sf::Color(255, 61, 57));
	lose_message.setPosition(150, 350);

	sf::Text continue_message;
	continue_message.setFont(font);
	continue_message.setString("LEFT-CLICK TO CONTINUE");
	continue_message.setCharacterSize(20);
	continue_message.setFillColor(sf::Color(255, 61, 57));
	continue_message.setPosition(280, 400);

	sf::Text clicks;
	clicks.setFont(font);
	clicks.setString("Clicks: " + clicks_counter);
	clicks.setCharacterSize(35);
	clicks.setFillColor(sf::Color(255, 61, 57));
	clicks.setPosition(200, 710);

	sf::Text level;
	level.setFont(font);
	level.setString("Level: " + level_counter);
	level.setCharacterSize(35);
	level.setFillColor(sf::Color(255, 61, 57));
	level.setPosition(500, 710);

	m_messages[WIN] = win_message;
	m_messages[LOSE] = lose_message;
	m_messages[CONTINUE] = continue_message;
	m_messages[CLICKS] = clicks;
	m_messages[LEVEL] = level;
}

