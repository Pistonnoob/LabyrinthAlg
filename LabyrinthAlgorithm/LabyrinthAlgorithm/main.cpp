//
//#include <SFML\Graphics.hpp>
//#include <stdlib.h>
//#include <ctime>
//
//const int WINDOW_WIDTH = 400;
//const int WINDOW_HEIGHT = 400;
//const int LABYRINTH_WIDTH = 50;
//const int LABYRINTH_HEIGHT = 50;
//
//
////Create the structure for the disjunkta mängder
//struct Node {
//	Node* p;
//	sf::Color c;
//	int r;
//	Node() { p = NULL; c = sf::Color::Red; r = 0; }
//	Node(Node* parent, sf::Color color, int rank = 0) { p = parent; c = color; r = rank; }
//}labyrinth[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];
//
////Create a list of corridors
//std::vector<std::pair<int, int>> corridor;
//
//
//
//int GetRand(int start, int length)
//{
//	return rand() % length + start;
//}
//
//std::pair<int, int> GetPos()
//{
//	return std::pair<int, int>(GetRand(0, LABYRINTH_WIDTH), GetRand(0, LABYRINTH_HEIGHT));
//}
//
//
//sf::RectangleShape ToShape(Node* node, int x, int y);
//
//Node* FindSet(Node* x)
//{
//	//Path compression
//	if (x != x->p)
//		x->p = FindSet(x->p);
//	x->c = x->p->c;
//	return x->p;
//}
//
//void Link(Node* x, Node* y)
//{
//	if (x->r > y->r)
//		y->p = x;
//	else
//	{
//		x->p = y;
//		if (x->r == y->r)
//			y->r++;
//	}
//}
//
//void Union(Node* x, Node* y)
//{
//	Link(FindSet(x), FindSet(y));
//}
//
//
//int main()
//{
//	srand(time(NULL));
//
//	//Create the rooms
//	for (int x = 0; x < LABYRINTH_WIDTH; x++)
//	{
//		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
//		{
//			labyrinth[x][y] = Node(&labyrinth[x][y], sf::Color(), 0);
//			labyrinth[x][y].c = sf::Color::White;
//			/*labyrinth[x][y].c.r += (int)((255 / LABYRINTH_WIDTH) * (x + 1));
//			labyrinth[x][y].c.g += (int)((255 / LABYRINTH_HEIGHT) * (y + 1));*/
//		}
//	}
//
//	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Labyrinth Algorithm");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//
//	//Do the algorithm
//	for (int x = 0; x < LABYRINTH_WIDTH; x += 2)
//	{
//		for (int y = 0; y < LABYRINTH_HEIGHT; y += 2)
//		{
//			if (x != LABYRINTH_WIDTH && y != LABYRINTH_HEIGHT)
//			{
//				int right = GetRand(0, 2);
//				std::pair <int, int> nodePos (right, 1 - right);
//				labyrinth[x + nodePos.first][y + nodePos.second].c.r += 10;
//				Union(&labyrinth[x][y], &labyrinth[x + nodePos.first][y + nodePos.second]);
//
//			}
//		}
//	}
//
//	for (int i = 0; i < 200; i++)
//	{
//		std::pair<int, int> pos = GetPos();
//		std::pair<int, int> nPos(0, 0);
//		int direction = GetRand(0, 4);
//		switch (direction)
//		{
//		case 0:	nPos = std::pair<int, int>(pos.first, pos.second - 1);
//			break;
//		case 1:	nPos = std::pair<int, int>(pos.first -1, pos.second);
//			break;
//		case 2:	nPos = std::pair<int, int>(pos.first, pos.second + 1);
//			break;
//		case 3:	nPos = std::pair<int, int>(pos.first + 1, pos.second);
//			break;
//		default:
//			break;
//		}
//		if (nPos.first < LABYRINTH_WIDTH && nPos.first >= 0 && nPos.second < LABYRINTH_HEIGHT && nPos.second >= 0)
//		{
//			Node* fNode = &labyrinth[pos.first][pos.second];
//			Node* sNode = &labyrinth[nPos.first][nPos.second];
//			if (FindSet(fNode) != FindSet(sNode))
//			{
//				sNode->c.r += 10;
//				fNode->c.r += 10;
//				Union(fNode, sNode);
//			}
//		}
//	}
//
//	//Draw the screen
//	window.clear();
//
//	for (int x = 0; x < LABYRINTH_WIDTH; x++)
//	{
//		for (int y = 0; y < LABYRINTH_HEIGHT; y++)
//		{
//			window.draw(ToShape(&labyrinth[x][y], x, y));
//		}
//	}
//
//
//	window.display();
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//	}
//	return 0;
//}
//
//sf::RectangleShape ToShape(Node* node, int x, int y)
//{
//	sf::RectangleShape rShape(sf::Vector2f(WINDOW_WIDTH / LABYRINTH_WIDTH, WINDOW_HEIGHT / LABYRINTH_HEIGHT));
//	rShape.setPosition(sf::Vector2f(x * (WINDOW_WIDTH / LABYRINTH_WIDTH), y * (WINDOW_HEIGHT / LABYRINTH_HEIGHT)));
//	rShape.setFillColor(node->c);
//	/*rShape.setOutlineThickness(1.0f);
//	rShape.setOutlineColor(sf::Color::Black);*/
//
//	return rShape;
//}
//
