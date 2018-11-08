#pragma once
#include<SFML\Graphics.hpp>
#include <vector>
#include <algorithm>
using namespace sf;
using namespace std;

class animation
{
public:
	animation(Texture* texture, Vector2u imageCount, float switchTime);
	~animation();

	void Update(int row, float deltaTime);
	void update(Sprite rect,bool gendre);
	void Move(Sprite &pacman, float deltaTime,animation &ani, RenderWindow &ingame,bool gendre);
public:
        IntRect uvRect;
		char u = 'f';
		float top, bottom, left, right;
		vector<Vector2i> tiles;
		int M;
		float speed = 0.5;
		struct canMove {
			bool up=true;
			bool down=true;
			bool right=true;
			bool left=true;
		}CanMove;
private:
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
};