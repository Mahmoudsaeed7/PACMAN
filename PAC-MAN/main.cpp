#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include "animation.h"
#include "Player.h"
#include "Menu.h"
#include "pickup.h"
#include"sound.h"
#include "Enemy.h"
using namespace std;
using namespace sf;
// for load map

sound s,s2;
Texture tileTexture;
Sprite tiles;
vector< vector< Vector2i > > maap;
vector< vector< int > > colMap;

Mutex mutex;
Mutex mutex2,mutex3,mutexwin;

int main();
void loadMap(const char*filename);
void loadColMap(const char*filename);
void credit();
void instructions();
void Win();
void StartGame();

int main()
{
	Thread thread(&instructions),thread3(&credit);
	Thread thread2(&StartGame);
	RenderWindow window(sf::VideoMode(800, 600), "PACMAN", sf::Style::Default);
	Font PACfont;
	Event event;
	Text logo;
	Texture PAC;
	Sprite look;
	Menu menu(800, 600);
	// display menu , Entrance 
	window.setPosition(Vector2i(290,70));
	PAC.loadFromFile("images/Pac-Man-PNG-Clipart.png");
	PAC.setSmooth(true);
	look.setTexture(PAC);
	look.setScale(Vector2f(0.6f, 0.6f)),look.setPosition(45,175);
	if (!PACfont.loadFromFile("Fonts/PAC-FONT.ttf"))
		throw("Error load font");
	logo.setFont(PACfont);
	logo.setCharacterSize(65);
	logo.setFillColor(Color::Yellow);
	logo.setString("PAC-MAN");
	logo.setStyle(Text::Bold);
	logo.setPosition(40, 70);

		s2.out();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case  Event::Closed:
				window.close();
				break;
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					s.passby();
					menu.moveUp();
					break;
				case Keyboard::Down:
					s.passby();
					menu.moveDown();
					break;
				case Keyboard::Return:
					s.choose();
					switch (menu.getPressedItem())
					{
					case 0:
						mutex2.lock();
						window.close();
						thread2.launch();
						mutex2.unlock();
						break;
					case 1:
						mutex.lock();
						window.close();
						thread.launch();
						mutex.unlock();
						break;
					case 2:
						mutex3.lock();
						window.close();
						thread3.launch();
						mutex3.unlock();
						break;
					case 3:
						window.close();
						break;
					default:
						break;
					}
				default:
					break;
				}
			default:
				break;
			}
		}
		window.clear();
		menu.draw(window);
		window.draw(logo),window.draw(look);
		window.display();
	}
	return 0;
}
// load map from files 
void loadMap(const char*filename) {
	ifstream openfile(filename);
	vector <Vector2i> tempMap;
	maap.clear();
	if (openfile.is_open()) {
		string tilelocation;
		openfile >> tilelocation;

		tileTexture.loadFromFile(tilelocation);
		tiles.setTexture(tileTexture);

		while (!openfile.eof()) {
			string str, value;
			getline(openfile, str);
			stringstream stream(str);
			while (getline(stream, value, ' ')) {
				if (value.length() > 0) {
					string xx = value.substr(0, value.find(',')), yy = value.substr(value.find(',') + 1);
					int x, y, i, j;
					for (i = 0; i < xx.length(); i++) {
						if (!isdigit(xx[i]))
							break;
					}
					for (j = 0; j < yy.length(); j++) {
						if (!isdigit(yy[j]))
							break;
					}
					x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
					y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

					tempMap.push_back(Vector2i(x, y));
				}
			}
			if (tempMap.size() > 0) {
				maap.push_back(tempMap);
				tempMap.clear();
			}
		}
		maap.push_back(tempMap);
	}
}
//load collision map from file 
void loadColMap(const char*filename) {
	ifstream openfile(filename);
	vector <int> tempMap;
	colMap.clear();
	if (openfile.is_open()) {
		while (!openfile.eof()) {
			string str, value;
			getline(openfile, str);
			stringstream stream(str);
			while (getline(stream, value, ' ')) {
				if (value.length() > 0) {
					int a = atoi(value.c_str());
					tempMap.push_back(a);
				}
			}
			colMap.push_back(tempMap);
			tempMap.clear();
		}
		colMap.push_back(tempMap);
	}
}
// display credits 
void credit() {
	mutex3.lock();
	Thread thr(&main);
	RenderWindow ingame(VideoMode(800, 600), "PACMAN", Style::Default);
	Event eVent;
	Font font;
	Text credit;
	string creditfile, s;
	font.loadFromFile("Fonts/6809 chargen.ttf");
	credit.setCharacterSize(23), credit.setFillColor(Color::Blue), credit.setFont(font), credit.setPosition(105, 80), credit.setString("   \t\t\tThis game is programmed by \n \n\t\t\t\t\t\t Mohamed Adel \n \n\t\t\t\t\t\t Mohamed Zaki\n \n\t\t\t\t\t\t Mostafa Khaled \n \n\t\t\t\t\t\t Mahmoud Saeed\n \n\t\t\t\t\t\t Motaz Medhat \n \n\t\t\t\t\t\t Bassant Hossam \n \n with help from Dr.Elshaimaa Hassan. \n To Faculty of computer and information science \n Release date : 1/5/2018 ");
	while (ingame.isOpen()) {
		while (ingame.pollEvent(eVent)) {
			if (eVent.type == Event::Closed) {
				ingame.close();
				thr.launch();
			}
			if (eVent.type == Event::KeyPressed) {
				if (eVent.key.code == Keyboard::Q) {
					ingame.close();
				}
				else if (eVent.key.code == Keyboard::Escape) {
					ingame.close();
					thr.launch();
				}
			}
		}
		ingame.clear();
		ingame.draw(credit);
		ingame.display();
	}
	mutex3.unlock();
}
// display instructions 
void instructions() {
	mutex.lock();
	RenderWindow ingame(VideoMode(800, 600), "PACMAN", Style::Default);
	Event eVent;
	Text Goal, Controls, Goaltext, Controlstext;
	Font font;
	Thread th(&main);
	if (!font.loadFromFile("Fonts/6809 chargen.ttf"))
		throw("Error load font");
	Goaltext.setCharacterSize(24), Controlstext.setCharacterSize(24), Goal.setCharacterSize(32), Controls.setCharacterSize(32);
	Goaltext.setFillColor(Color::White), Controlstext.setFillColor(Color::White), Goal.setFillColor(Color::Green), Controls.setFillColor(Color::Green);
	Goaltext.setFont(font), Controlstext.setFont(font), Goal.setFont(font), Controls.setFont(font);
	Goal.setPosition(370, 90), Goaltext.setPosition(2, 140), Controls.setPosition(342, 290), Controlstext.setPosition(2, 340);
	Goal.setString("Goal"), Controls.setString("Controls"), Goaltext.setString(" Guide Pacman around the maze and eat all the little white\ndots whilst avoiding those nasty ghosts. If you eat a Power\n Pill,you can eat the ghosts! Occasionally, a fruit appears\n which gives you a bonus score when eaten."), Controlstext.setString(" Arrow keys for Pacman \n Q : Quit game \n ");
	while (ingame.isOpen()) {
		while (ingame.pollEvent(eVent)) {
			if (eVent.type == Event::Closed) {
				ingame.close();
				th.launch();
			}
			if (eVent.type == Event::KeyPressed) {
				if (eVent.key.code == Keyboard::Q) {
					ingame.close();
				}
				else if (eVent.key.code == Keyboard::Escape) {
					ingame.close();
					th.launch();
				}
			}
		}
		ingame.clear();
		ingame.draw(Goal), ingame.draw(Goaltext), ingame.draw(Controls), ingame.draw(Controlstext);
		ingame.display();
	}
	mutex.unlock();
}
// when all dots have been eaten 
void Win() {
	mutexwin.lock();
	RenderWindow window(VideoMode(800, 650), "PACMAN", Style::Default);
	Event event;
	Thread endthread(&main);
	Texture win;
	win.loadFromFile("images/new_win.jpg");
	Sprite Win;
	Win.setScale(1.1f, 1.1f);
	Win.setTexture(win);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed || event.type == Event::Closed) {
				window.close();
				endthread.launch();
			}
		}
		window.clear(Color::Black);
		window.draw(Win);
		window.display();
	}
	mutexwin.unlock();
}
void StartGame() {
	mutex2.lock();
	RenderWindow ingame(VideoMode(730, 675, 28), "PACMAN", Style::Default);
	ingame.setPosition(Vector2i(290, 20));
	Event eVent;
	Clock clock;
	Thread th(&main);
	Sprite mrPacman, msPacman;
	Texture mrPacmantext, msPacmantext;
	Text Name, dis;
	long long score = 0;
	Font font;
	string name, Gender, display;
	Menu menu(800, 710);
	bool flag = 0, flag2 = 0, MsOrMr = 1;
	font.loadFromFile("Fonts/6809 chargen.ttf");
	Name.setFont(font), Name.setPosition(50, 70), Name.setCharacterSize(34), Name.setFillColor(Color::Yellow), Name.setString("Mr OR Ms PACMAN? \n");
	/*
	Texture enemyText;
	enemyText.loadFromFile("images/blinky.png");

	Enemy enemy1;
	enemy1.sprite.setTexture(enemyText);
	enemy1.sprite.setScale(1.8f, 1.8f);
	*/
	Player player(mrPacman, mrPacmantext, Vector2f(295.0f, 483.0f), Vector2f(1.7f, 1.7f), "images/pacman123.png"), player2(msPacman, msPacmantext, Vector2f(292.0f, 483.0f), Vector2f(1.7f, 1.7f), "images/mspacman.png");
	animation mrPacmananim(&player.playerTexture, Vector2u(3, 4), 0.05f), msPacmananim(&player2.playerTexture, Vector2u(3, 4), 0.05f);


	float deltaTime = 0.0f;
	loadMap("Texts/map1.txt");
	loadColMap("Texts/Col1.txt");
	dis.setFont(font);
	dis.setPosition(650, 10);
	dis.setCharacterSize(25);

	vector<pickup>::const_iterator it;
	vector<pickup> pickupArray;
	pickup pickup1;
	int count;
	pickup1.sprite.setTexture(pickup1.dotText);

	Texture load;
	load.loadFromFile("images/loading.jpg");
	Sprite loading;
	loading.setTexture(load);

	Thread Youwin(&Win);

	for (int k = 0; k < 1; k++) {
		for (int i = 0; i < maap.size(); i++) {
			for (int j = 0; j < maap[i].size(); j++) {
				if (maap[i][j].x == -1 && maap[i][j].y == -1) {
					pickup1.rect.setPosition(j * 33, i * 33);
					pickupArray.push_back(pickup1);
				}
				ingame.draw(loading);
			}
			ingame.display();
		}
	}
	while (ingame.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		while (ingame.pollEvent(eVent)) {
			switch ((eVent.type))
			{
			case Event::Closed:
				ingame.close();
				th.launch();
				break;
			case Event::KeyReleased:
				switch (eVent.key.code)
				{
				case Keyboard::Right:
					menu.moveRight();
					break;
				case Keyboard::Left:
					menu.moveLeft();
					break;
				case Keyboard::Q:
					ingame.close();
					break;
				case Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						flag = true;
						break;
					case 1:
						flag2 = true;
						break;
					default:
						break;
					}
				default:
					break;
				}
			default:
				break;
			}
		}
		/*
		enemy1.update();
		enemy1.updateMovement();
		enemy1.update(enemy1.sprite);
		for (int i = 0; i < enemy1.tiles.size(); i++) {
			if (colMap[enemy1.tiles[i].y][enemy1.tiles[i].x] == 1) {
				if (enemy1.direction == 2) {
					enemy1.CanMove.up = false;
					enemy1.rect.move(0, 1);
				}
				else if (enemy1.direction == 3) {
					enemy1.CanMove.down = false;
					enemy1.rect.move(0, -1);
				}
				else if (enemy1.direction == 0) {
					enemy1.CanMove.right = false;
					enemy1.rect.move(-1, 0);
				}
				else if (enemy1.direction == 1) {
					enemy1.CanMove.left = false;
					enemy1.rect.move(1, 0);
				}
				break;
			}
			*/
			if (flag) {
				mrPacmananim.Move(player.player, deltaTime, mrPacmananim, ingame, MsOrMr);
				player.player.setTextureRect(mrPacmananim.uvRect);
				mrPacmananim.update(player.player, flag);

				for (int i = 0; i < mrPacmananim.tiles.size(); i++) {
					if (colMap[mrPacmananim.tiles[i].y][mrPacmananim.tiles[i].x] == 1) {
						if (mrPacmananim.M == 2) {
							mrPacmananim.CanMove.up = false;
							player.player.move(0, 1);
						}
						else if (mrPacmananim.M == 3) {
							mrPacmananim.CanMove.down = false;
							player.player.move(0, -1);
						}
						else if (mrPacmananim.M == 0) {
							mrPacmananim.CanMove.right = false;
							player.player.move(-1, 0);
						}
						else if (mrPacmananim.M == 1) {
							mrPacmananim.CanMove.left = false;
							player.player.move(1, 0);
						}
						break;
					}
				}

				count = 0;
				for (it = pickupArray.begin(); it != pickupArray.end(); it++) {
					if (player.player.getGlobalBounds().intersects(pickupArray[count].rect.getGlobalBounds())) {
						score++;
						s.eat();
						pickupArray[count].destroy = true;
					}
					count++;
				}

				count = 0;
				for (it = pickupArray.begin(); it != pickupArray.end(); it++) {
					if (pickupArray[count].destroy == true) {
						pickupArray.erase(it);
						break;
					}
					count++;
				}
			}
			else if (flag2) {
				MsOrMr = 0;
				msPacmananim.Move(player2.player, deltaTime, msPacmananim, ingame, MsOrMr);
				player2.player.setTextureRect(msPacmananim.uvRect);
				msPacmananim.update(player2.player, flag);

				for (int i = 0; i < msPacmananim.tiles.size(); i++) {
					if (colMap[msPacmananim.tiles[i].y][msPacmananim.tiles[i].x] == 1) {
						if (msPacmananim.M == 2) {
							msPacmananim.CanMove.up = false;
							player2.player.move(0, 1);
						}
						else if (msPacmananim.M == 3) {
							msPacmananim.CanMove.down = false;
							player2.player.move(0, -1);
						}
						else if (msPacmananim.M == 1) {
							msPacmananim.CanMove.right = false;
							player2.player.move(-1, 0);
						}
						else if (msPacmananim.M == 0) {
							msPacmananim.CanMove.left = false;
							player2.player.move(1, 0);
						}
						break;
					}
				}

				count = 0;
				for (it = pickupArray.begin(); it != pickupArray.end(); it++) {
					if (player2.player.getGlobalBounds().intersects(pickupArray[count].rect.getGlobalBounds())) {
						score++;
						s.eat();
						pickupArray[count].destroy = true;
					}
					count++;
				}

				count = 0;
				for (it = pickupArray.begin(); it != pickupArray.end(); it++) {
					if (pickupArray[count].destroy == true) {
						pickupArray.erase(it);
						break;
					}
					count++;
				}
			}
			ingame.clear(Color::Black);
			if (flag || flag2) {
				for (int i = 0; i < maap.size(); i++) {
					for (int j = 0; j < maap[i].size(); j++) {
						if (maap[i][j].x != -1 && maap[i][j].y != -1 && maap[i][j].x != 9 && maap[i][j].y != 9) {
							tiles.setPosition(j * 32, i * 32);
							tiles.setTextureRect(IntRect(maap[i][j].x * 49, maap[i][j].y * 50, 29, 29));
							ingame.draw(tiles);
						}
					}
				}
				count = 0;
				for (it = pickupArray.begin(); it != pickupArray.end(); it++) {
					pickupArray[count].update();
					ingame.draw(pickupArray[count].rect);
					ingame.draw(pickupArray[count].sprite);
					count++;
				}

			    //ingame.draw(enemy1.sprite);

				dis.setString(to_string(score));
				ingame.draw(dis);
				if (flag)
					ingame.draw(player.player);
				else if (flag2)
					ingame.draw(player2.player);
			}
			else
				ingame.draw(menu.Gendre[0]), ingame.draw(menu.Gendre[1]), ingame.draw(Name);
			if (score == 151) {
				ingame.close();
				Youwin.launch();
			}
			ingame.display();
		}
		mutex2.unlock();
}