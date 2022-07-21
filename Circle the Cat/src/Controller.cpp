#include <Controller.h>




Controller::Controller() : m_curent_level(0), m_render_window(sf::RenderWindow(sf::VideoMode(800, 800), "Circle the Cat", sf::Style::Close))
{
    m_render_window.setFramerateLimit(60);
    m_render_window.setVerticalSyncEnabled(true);
    std::srand(static_cast<unsigned int>(std::time(NULL)));
}

void Controller::run()
{
    auto game_window = GameWindow(m_curent_level);

    sf::Vector2f location;

    while (m_render_window.isOpen())
    {
        m_render_window.clear(sf::Color::White);
        game_window.draw_screen(m_render_window);
        m_render_window.display();
        check_level_status(game_window);
        

        auto event = sf::Event();
        if (game_window.get_animation_status())
        {
            event = sf::Event();
            game_window.set_animation_status(false);
        }

        while (m_render_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_render_window.close();
                break;
            case sf::Event::MouseMoved:
                location = (sf::Vector2f)sf::Mouse::getPosition(m_render_window);
                game_window.handleMouseHover(location);
                break;
            case sf::Event::MouseButtonReleased:
                location = (sf::Vector2f)sf::Mouse::getPosition(m_render_window);
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    game_window.press(location, m_render_window);
                    break;
                }
                break;
            }
        }
    }
}

void Controller::check_level_status(GameWindow& game_window)
{
    if (GameManager::instance().is_level_won())
    {
        message_screen(game_window, WIN);
        game_window.reset(++m_curent_level);
    }
    else if (GameManager::instance().is_level_lost())
    {
        message_screen(game_window, LOSE);
        game_window.reset(m_curent_level);
    }
    else if (GameManager::instance().is_level_reset())
    {
        game_window.reset(m_curent_level);
    }
}

void Controller::message_screen(GameWindow& game_window, const std::string& type)
{
    auto background = sf::RectangleShape(sf::Vector2f(800.f, 700.f));
    
    for (int i = 0; i < 255; i += 2)
    {
        background.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)i));
        m_render_window.draw(background);
        m_render_window.display();
    }

    while (m_render_window.isOpen())
    {
        m_render_window.clear(sf::Color::White);
        game_window.draw_message_screen(type, m_render_window);
        m_render_window.display();

        if (auto event = sf::Event{};  m_render_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_render_window.close();
                break;
            case sf::Event::MouseButtonReleased:

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    return;
                }
            }
        }
    }
}
