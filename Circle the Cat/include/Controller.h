#include <GameWindow.h>



class Controller
{
	int m_curent_level;
	sf::RenderWindow m_render_window;

	void check_level_status(GameWindow&);
	void message_screen(GameWindow&, const std::string&);

public:

	Controller();

	void run();
};