#include "pickup.h"



pickup::pickup()
{
	dotText.loadFromFile("images/dot2.png");
	rect.setFillColor(Color::Black);
	rect.setSize(Vector2f(12, 12));
}

pickup::~pickup()
{
}

void pickup::update()
{
	sprite.setPosition(rect.getPosition());
}
