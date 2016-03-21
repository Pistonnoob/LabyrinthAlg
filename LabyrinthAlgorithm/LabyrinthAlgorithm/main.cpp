
#include<SFML\Graphics.hpp>

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int LABYRINTH_WIDTH = 200;
const int LABYRINTH_HEIGHT = 200;

//Create the structure for the disjunkta mängder
struct Node {
	Node* p;
	sf::Color c;
	int r;
	Node() { p = NULL; c = sf::Color::Red; r = 0; }
	Node(Node* parent, sf::Color color, int rank = 0) { p = parent; c = color; r = rank; }
}labyrinth[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];

sf::RectangleShape toShape(Node* node, int x, int y);

Node* FindSet(Node* x)
{
	return x;
}

void Link(Node* x, Node* y)
{

}

void Union(sf::Vector2i f, sf::Vector2i s)
{

}


int main()
{

	//Create the shapes
	for (int x = 0; x < LABYRINTH_WIDTH; x++)
	{
		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
		{
			labyrinth[x][y] = Node(&labyrinth[x][y], sf::Color(), 0);
			labyrinth[x][y].c.r += (int)((255 / LABYRINTH_WIDTH) * (x + 1));
			labyrinth[x][y].c.g += (int)((255 / LABYRINTH_HEIGHT) * (y + 1));
		}
	}

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Labyrinth Algorithm");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//Do the algorithm
	
	//Draw the screen
	window.clear();

	for (int x = 0; x < LABYRINTH_WIDTH; x++)
	{
		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
		{
			window.draw(toShape(&labyrinth[x][y], x, y));
		}
	}

	window.display();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		

	}

	return 0;
}

sf::RectangleShape toShape(Node* node, int x, int y)
{
	sf::RectangleShape rShape(sf::Vector2f(WINDOW_WIDTH / LABYRINTH_WIDTH, WINDOW_HEIGHT / LABYRINTH_HEIGHT));
	rShape.setPosition(sf::Vector2f(x * (WINDOW_WIDTH / LABYRINTH_WIDTH), y * (WINDOW_HEIGHT / LABYRINTH_HEIGHT)));
	rShape.setFillColor(node->c);
	return rShape;
}