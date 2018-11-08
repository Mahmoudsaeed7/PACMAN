#include "sound.h"
#include<iostream>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;
Music m,m2;
SoundBuffer buff, b;
Sound s, ss;
void sound::out()
{
	m2.openFromFile("Sounds/nice_music.ogg");
	m2.setLoop(true);
	m2.setVolume(25);
	m2.play();
}
void sound::passby()
{
	m.openFromFile("Sounds/oh-boy.OGG");
	m.setVolume(5);
	m.play();
}
void sound::choose()
{
	m.openFromFile("Sounds/ow1.wav");
	m.setVolume(100);
	m.play();
}
void sound::eat()
{
	m.openFromFile("Sounds/wakka_wakka1.wav");
	m.setVolume(5);
	m.play();
}
void sound::win()
{
	m.openFromFile("Sounds/applauses.ogg");
	m.setVolume(100);
	m.play();
}
