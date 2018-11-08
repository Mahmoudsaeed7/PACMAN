#include "Enemy.h"



Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(29, 29));
	rect.setPosition(255, 283);
	rect.setFillColor(sf::Color::White);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	sprite.setPosition(rect.getPosition());
}

void Enemy::updateMovement()
{
	if (direction == 0) {
		if (CanMove.right) {
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(IntRect(0, 16 * direction, 16, 16));
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	else if (direction == 1) {
		if (CanMove.left) {
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(IntRect(0, 16 * direction, 16, 16));
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	else if (direction == 2) {
		if (CanMove.up) {
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(IntRect(0, 16 * direction, 16, 16));
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	else if (direction == 3) {
		if (CanMove.down) {
			rect.move(0, movementSpeed);
			sprite.setTextureRect(IntRect(0, 16 * direction, 16, 16));
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	counterWalking++;
	if (counterWalking == 1) {
		counterWalking = 0;
	}
	counter++;
	if (counter >= 50) {
		direction = generateRandom(3);
		counter = 0;
	}

}
int Enemy::generateRandom(int max)
{
	int randomNumber = rand() % max ;
	return randomNumber;
}

void Enemy::update(Sprite rect)
{
		bottom = rect.getPosition().y +29;
		left = rect.getPosition().x ;
		right = rect.getPosition().x +29;
		top = rect.getPosition().y ;

	Vector2i topLeft(Vector2i((int)left / 32, (int)top / 32));
	Vector2i topRight(Vector2i((int)right / 32, (int)top / 32));
	Vector2i bottomLeft(Vector2i((int)left / 32, (int)bottom / 32));
	Vector2i bottomRight(Vector2i((int)right / 32, (int)bottom / 32));
	tiles.clear();

	tiles.push_back(topLeft);
	if (find(tiles.begin(), tiles.end(), topRight) == tiles.end())tiles.push_back(topRight);
	if (find(tiles.begin(), tiles.end(), bottomLeft) == tiles.end())tiles.push_back(bottomLeft);
	if (find(tiles.begin(), tiles.end(), bottomRight) == tiles.end())tiles.push_back(bottomRight);
}