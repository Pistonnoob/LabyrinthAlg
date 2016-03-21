
#include<SFML\Graphics.hpp>


const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int LABYRINTH_WIDTH = 200;
const int LABYRINTH_HEIGHT = 200;

int main()
{
	//Create the structure for the disjunkta mängder
	struct Node {
		Node* p;
		sf::Color c;
		int accessed;
		Node() { p = NULL; c = sf::Color::Red; accessed = 0; }
		Node(Node* parent, sf::Color color, int accessed = 4) { p = parent; c = color; accessed = accessed; }
	}labyrinth[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];

	for (int x = 0; x < LABYRINTH_WIDTH; x++)
	{
		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
		{
			labyrinth[x][y] = Node(&labyrinth[x][y], sf::Color::Red, 4);
			labyrinth[x][y].c.r -= 255 % (int)((255 / LABYRINTH_WIDTH) * x);
			labyrinth[x][y].c.g -= 255 % (int)((255 / LABYRINTH_HEIGHT) * y);
		}
	}

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Labyrinth Algorithm");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//Create the shapes

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (int x = 0; x < LABYRINTH_WIDTH; x++)
		{
			for (int y = 0; y < LABYRINTH_HEIGHT; y++)
			{
			}
		}

		window.display();
	}

	return 0;
}