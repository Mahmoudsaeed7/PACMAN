#pragma once
#include <Sfml/Graphics.hpp>
using namespace sf;
class Player
{
public:
	Player(Sprite &player, Texture &playerTexture, Vector2f postion, Vector2f scale, const char*fileName);
	~Player();
public:
	Texture playerTexture;
	Sprite player;
};