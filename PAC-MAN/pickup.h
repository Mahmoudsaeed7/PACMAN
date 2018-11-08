#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class pickup
{
public:
	pickup();
	~pickup();
public:
	bool isDot = true;
	Sprite sprite;
	bool destroy = false;
	Texture dotText;
	RectangleShape rect;
public:
	void update();
};

