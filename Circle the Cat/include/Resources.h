

const sf::Color UNPRESSED = sf::Color(204, 255, 0);
const sf::Color PRESSED = sf::Color(114, 133, 0);
const sf::Color HOVER = sf::Color(160, 204, 0);

const int FRAMES = 9;
const int FACTOR = 5;
const int START = 5;
const int CIRCLE_RADIUS = 30;

const std::string WIN = "win";
const std::string LOSE = "lose";
const std::string CONTINUE = "continue";
const std::string CLICKS = "clicks";
const std::string LEVEL = "level";

struct Range
{
	int min, max;
};

const Range HIGH = { 40, 50 };
const Range NORMAL = { 20, 25 };
const Range LOW = { 8, 10 };
const Range VERY_LOW = { 3, 5 };


enum class Difficulty
{
	EASY,
	MEDIUM,
	HARD,
	EXTREME
};

enum class Row
{
	FIRST = 10,
	SECOND = 122,
	THIRD = 234
};

enum class Orientation
{
	NORMAL = 1,
	REVERSE = -1
};

enum Texture
{
	CAT,
	RESET,
	BACK
};

enum Direction
{
	UP_LEFT,
	UP_RIGHT,
	LEFT,
	RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
	LAST_MOVE
};