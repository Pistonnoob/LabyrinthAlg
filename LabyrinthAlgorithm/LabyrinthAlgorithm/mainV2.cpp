
#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int LABYRINTH_WIDTH = 400;
const int LABYRINTH_HEIGHT = 400;
const int CELL_WIDTH = WINDOW_WIDTH / LABYRINTH_WIDTH;
const int CELL_HEIGHT = WINDOW_HEIGHT / LABYRINTH_HEIGHT;
const int WALL_THICKNESS = 1;
//Create the structure for the disjunkta m�ngder
struct Node {
	Node* p;
	sf::Color c;
	int r;
	Node() { p = NULL; c = sf::Color::Red; r = 0;}
	Node(Node* parent, sf::Color color, int rank = 0) {	p = parent; c = color; r = rank;}
}labyrinth[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];

struct Wall {
	int x, y, w, h;	//For rendering reasons
	Node* first;
	Node* second;
};

//Create a list of walls
std::vector<Wall*> walls;
std::vector<Wall*> checkedWalls;

int GetRand(int start, int length)
{
	return rand() % length + start;
}

std::pair<int, int> GetPos()
{
	return std::pair<int, int>(GetRand(0, LABYRINTH_WIDTH), GetRand(0, LABYRINTH_HEIGHT));
}


sf::RectangleShape ToShape(Node* node, int x, int y);

Node* FindSet(Node* x)
{
	//Path compression
	if (x != x->p)
		x->p = FindSet(x->p);
	x->c = x->p->c;
	return x->p;
}

void Link(Node* x, Node* y)
{
	if (x->r > y->r)
		y->p = x;
	else
	{
		x->p = y;
		if (x->r == y->r)
			y->r++;
	}
}

void Union(Node* x, Node* y)
{
	Link(FindSet(x), FindSet(y));
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(unsigned(time(NULL)));
	sf::Clock timer;
	sf::Time algTime, runTime, setupTime, renderTime;

	int groups = LABYRINTH_WIDTH * LABYRINTH_HEIGHT;



	//Create the rooms
	for (int x = 0; x < LABYRINTH_WIDTH; x++)
	{
		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
		{
			//Set the cell color
			labyrinth[x][y] = Node(&labyrinth[x][y], sf::Color::White, 0);	
		}
	}
	//Create the walls
	for (int x = 0; x < LABYRINTH_WIDTH; x++)
	{
		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
		{
			if (x < LABYRINTH_WIDTH - 1)
			{	//Create a "right" wall
				Wall* nodeWall = new Wall;
				nodeWall->first = &labyrinth[x][y];
				nodeWall->second = &labyrinth[x + 1][y];
				nodeWall->x = (x + 1) * CELL_WIDTH;
				nodeWall->y = (y)* CELL_HEIGHT;
				nodeWall->w = WALL_THICKNESS;
				nodeWall->h = CELL_HEIGHT;
				walls.push_back(nodeWall);
			}
			if (y < LABYRINTH_HEIGHT - 1)
			{	//Create a "down" wall
				Wall* nodeWall = new Wall;
				nodeWall->first = &labyrinth[x][y];
				nodeWall->second = &labyrinth[x][y + 1];
				nodeWall->x = (x)* CELL_WIDTH;
				nodeWall->y = (y + 1)* CELL_HEIGHT;
				nodeWall->w = CELL_WIDTH;
				nodeWall->h = WALL_THICKNESS;
				walls.push_back(nodeWall);
			}
		}
	}

#pragma region
	//Create the outline of the grid
	Wall* top = new Wall();
	top->x = CELL_WIDTH;
	top->y = 0;
	top->w = WINDOW_WIDTH - CELL_WIDTH;
	top->h = 1;
	top->first = NULL;
	top->second = NULL;
	checkedWalls.push_back(top);
	Wall* left = new Wall();
	left->x = 0;
	left->y = CELL_HEIGHT;
	left->w = 1;
	left->h = WINDOW_HEIGHT - CELL_HEIGHT;
	left->first = NULL;
	left->second = NULL;
	checkedWalls.push_back(left);
	Wall* down = new Wall();
	down->x = 0;
	down->y = WINDOW_HEIGHT-1;
	down->w = WINDOW_WIDTH - CELL_WIDTH;
	down->h = 1;
	down->first = NULL;
	down->second = NULL;
	checkedWalls.push_back(down);
	Wall* right = new Wall();
	right->x = WINDOW_WIDTH-1;
	right->y = 0;
	right->w = 1;
	right->h = WINDOW_HEIGHT - CELL_HEIGHT;
	right->first = NULL;
	right->second = NULL;
	checkedWalls.push_back(right);
#pragma endregion outline
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Labyrinth Algorithm");

	setupTime = algTime = timer.getElapsedTime();
	
	//I count the time used to randomize the wall access as time used for the algorithm. Because it is part of the algorithm.
	auto engine = std::default_random_engine{};
	//std::shuffle(std::begin(walls), std::end(walls), engine);
	std::random_shuffle(std::begin(walls), std::end(walls));


	int misses = 0;
	while (groups > 1)
	{
		if (walls.size() == 0)
		{
			std::cout << "The walls were emptied, something went wrong." << std::endl;
			break;
		}
		Wall* wallToRemove = walls.back();
		Node* m_first = wallToRemove->first;
		Node* m_second = wallToRemove->second;
		if (FindSet(m_first) != FindSet(m_second))
		{
			//Bind them together
			Union(m_first, m_second);
			groups--;
			delete wallToRemove;
		}
		else
		{
			misses++;
			checkedWalls.push_back(wallToRemove);
		}
		walls.pop_back();
	}
	renderTime = timer.getElapsedTime();
	algTime = renderTime - algTime;
	//Draw the screen
	window.clear();
	sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	background.setFillColor(sf::Color::White);
	window.draw(background);
	if (WINDOW_WIDTH > LABYRINTH_WIDTH || WINDOW_HEIGHT > LABYRINTH_HEIGHT)
	{
		for (std::vector<Wall*>::const_iterator index = walls.begin(); index != walls.end(); index++)
		{
			sf::RectangleShape line(sf::Vector2f((*index)->w, (*index)->h));
			line.setPosition(sf::Vector2f((*index)->x, (*index)->y));
			line.setFillColor(sf::Color::Black);
			window.draw(line);
		}
		for (std::vector<Wall*>::const_iterator index = checkedWalls.begin(); index != checkedWalls.end(); index++)
		{
			sf::RectangleShape line(sf::Vector2f((*index)->w, (*index)->h));
			line.setPosition(sf::Vector2f((*index)->x, (*index)->y));
			line.setFillColor(sf::Color::Black);
			window.draw(line);
		}
	}
	window.display();
	runTime = timer.getElapsedTime();
	renderTime = runTime - renderTime;

	std::cout << "Number of misses: " << misses << ". " << std::endl<< "Setup timer: " << setupTime.asSeconds() << ".\nAlgorithm timer: " << algTime.asSeconds() << ".\nRender timer: " << renderTime.asSeconds() << ".\nRun time of execution: " << runTime.asSeconds() << "." << std::endl;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	while (walls.size())
	{
		delete walls.back();
		walls.pop_back();
	}
	while (checkedWalls.size())
	{
		delete checkedWalls.back();
		checkedWalls.pop_back();
	}

	return 0;
}

sf::RectangleShape ToShape(Node* node, int x, int y)
{
	sf::RectangleShape rShape(sf::Vector2f(WINDOW_WIDTH / LABYRINTH_WIDTH, WINDOW_HEIGHT / LABYRINTH_HEIGHT));
	rShape.setPosition(sf::Vector2f(x * (WINDOW_WIDTH / LABYRINTH_WIDTH), y * (WINDOW_HEIGHT / LABYRINTH_HEIGHT)));
	rShape.setFillColor(node->c);
	/*rShape.setOutlineThickness(1.0f);
	rShape.setOutlineColor(sf::Color::Black);*/

	return rShape;
}

