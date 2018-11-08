#include "animation.h"


animation::animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x /3 ;
	uvRect.height =  texture->getSize().y /4 ;
}

animation::~animation()
{
}

void animation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	uvRect.left = currentImage.x*uvRect.width;
	uvRect.top = currentImage.y*uvRect.height;
}

void animation::update(Sprite rect,bool gendre)
{
	if (!gendre) {
		bottom = rect.getPosition().y + 28; 
		left = rect.getPosition().x + 6; 
		right = rect.getPosition().x + 28; 
		top = rect.getPosition().y + 6;
	}
	else {
		bottom = rect.getPosition().y +  26;
		left = rect.getPosition().x + 5;
		right = rect.getPosition().x + 24;
		top = rect.getPosition().y + 5;
	}

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

void animation::Move(Sprite &pacman,float deltaTime,animation &ani,RenderWindow &ingame,bool gendre)
{
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		u = 'w';
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		u = 's';
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		u = 'd';
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		u = 'a';
	}
	if (u == 'w') {
		if (CanMove.up) {
			M = 2;
			ani.Update(M, deltaTime);
			pacman.move(0.0f, -speed); 
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	else if (u == 's') {
		if (CanMove.down) {
			M = 3;
			ani.Update(M, deltaTime);
			pacman.move(0.0f,speed);
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	else if (u == 'd') {
		if (CanMove.right) {
			if (gendre)
				M = 0;
			else
				M = 1;
			ani.Update(M, deltaTime);
			pacman.move(speed, 0.0f);
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	else if (u == 'a') {
		if (CanMove.left) {
			if (gendre)
				M = 1;
			else
				M = 0;
			ani.Update(M, deltaTime);
			pacman.move(-speed, 0.0f);
			CanMove.up = true;
			CanMove.down = true;
			CanMove.left = true;
			CanMove.right = true;
		}
	}
	if (pacman.getPosition().x >= ingame.getSize().x)
	{
		pacman.setPosition(0.f, pacman.getPosition().y);
	}
	else if (pacman.getPosition().x <= 0)
	{
		pacman.setPosition(ingame.getSize().x, pacman.getPosition().y);
	}
}