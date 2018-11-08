#include "Menu.h"



Menu::Menu(float width, float height)
{
	font.loadFromFile("Fonts/6809 chargen.ttf");

	for (int i = 0; i < MAX_Number_OF_TEXT; i++) {
		menu[i].setFont(font);
		menu[i].setPosition(Vector2f(width / 2 + 70, height / (MAX_Number_OF_TEXT + 1)*(i+1)));
		menu[i].setCharacterSize(30);
	}

	Gendre[0].setFont(font);
	Gendre[0].setPosition(width / 2-200, height / (MAX_Number_OF_TEXT + 1) * 1+50);
	Gendre[0].setCharacterSize(27);
	Gendre[0].setFillColor(Color::Blue);
	Gendre[0].setString("Mr");

	Gendre[1].setFont(font);
	Gendre[1].setPosition(width / 2+60, height / (MAX_Number_OF_TEXT + 1) * 1+50);
	Gendre[1].setCharacterSize(27);
	Gendre[1].setFillColor(Color::White);
	Gendre[1].setString("Ms");

	menu[0].setFillColor(Color::Blue);
	menu[0].setString("NEW GAME");

	menu[1].setFillColor(Color::White);
	menu[1].setString("Instructions");


	menu[2].setFillColor(Color::White);
	menu[2].setString("Credits");

	menu[3].setFillColor(Color::White);
	menu[3].setString("Exit Game");

	selectedGendreIndex = 0;
	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(RenderWindow & window)
{
	for (int i = 0; i < MAX_Number_OF_TEXT; i++) {
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Blue);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_Number_OF_TEXT) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++ ;
		menu[selectedItemIndex].setFillColor(Color::Blue);
	}
}

void Menu::moveRight()
{
	if (selectedGendreIndex +  1 < 2){
		Gendre[selectedGendreIndex].setFillColor(Color::White);
		selectedGendreIndex++;
		Gendre[selectedGendreIndex].setFillColor(Color::Blue);
	}
}

void Menu::moveLeft()
{
	if (selectedGendreIndex - 1 >= 0) {
		Gendre[selectedGendreIndex].setFillColor(Color::White);
		selectedGendreIndex--;
		Gendre[selectedGendreIndex].setFillColor(Color::Blue);
	}
}

int Menu::getPressedItem()
{
	return selectedItemIndex;
}
int Menu::GetPressedItem()
{
	return selectedGendreIndex;
}

