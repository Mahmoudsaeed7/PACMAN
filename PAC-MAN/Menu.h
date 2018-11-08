#pragma once
#include <SFML\Graphics.hpp>
#define MAX_Number_OF_TEXT 4 
using namespace sf;
class Menu
{
public:
	Menu(float width,float height);
	~Menu();
public:
	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	int getPressedItem();
	int GetPressedItem();
	Text menu[MAX_Number_OF_TEXT],Gendre[2];
private:
	int selectedItemIndex,selectedGendreIndex;
	Font font;
};

