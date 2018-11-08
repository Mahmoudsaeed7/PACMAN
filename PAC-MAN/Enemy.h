#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Enemy
{
public:
	Enemy();
	~Enemy();
public:
	float movementSpeed = 0.8;
	int counter = 0;
	int counterWalking = 0;
	int direction = 0; 
	RectangleShape rect;
	Sprite sprite;
	float top, bottom, left, right;
	vector<Vector2i> tiles;
	struct canMove {
		bool up = true;
		bool down = true;
		bool right = true;
		bool left = true;
	}CanMove;
public:
	void update();
	void update(Sprite rect);
	void updateMovement();
	int generateRandom(int max);
};

