#include "Player.h"



Player::Player(Sprite &player, Texture &playerTexture,Vector2f postion,Vector2f scale,const char*fileName)
{
	player.setPosition(postion);
	playerTexture.loadFromFile(fileName);
	playerTexture.setSmooth(true);
	this -> playerTexture = playerTexture;
	player.setTexture(playerTexture);
	player.setScale(scale);
	this->player = player;
}

Player::~Player()
{
}
