/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include "player.h"

class Opponent {
public:
	Texture tex;
	Sprite sprite;
	float speed = 1;
	float xPos, yPos;
	int activeFace;
	ARRAY<string> trans;
	Opponent(){}
	Opponent(ARRAY<string> * trans)
	{
	
		xPos = 500; yPos = 800;
		activeFace = 0;
		this->trans = *trans;
		tex.loadFromFile(trans->data[activeFace]);
	
		sprite.setTexture(tex);
		sprite.setPosition(xPos, yPos);
		sprite.setScale(0.75, 0.75);
	}
	void setPosition(int newX, int newY)
	{
		xPos = newX;
		yPos = newY;
		sprite.setPosition(xPos, yPos);
	}
	void rotate(string transformation)
	{
		if (transformation == "l")
			activeFace = 1;
		else if (transformation == "r")
			activeFace = 2;
		else if (transformation == "u")
			activeFace = 0;
		else if (transformation == "d")
			activeFace = 3;
		tex.loadFromFile(trans[activeFace]);
		sprite.setTexture(tex);
	}
	void move(string s) {
		float delta_x = 0, delta_y = 0;
		if (activeFace == 0)
		{
			if (s == "u")
				delta_y = -1;
			else
				return rotate(s);
		}
		else if (activeFace == 1) //   <-
		{

			if (s == "l")
				delta_x = -1;
			else
				return rotate(s);
		}
		else if (activeFace == 2)   //->
		{
			if (s == "r")
				delta_x = 1;
			else
				return rotate(s);
		}
		else if (activeFace == 3)
		{
			if (s == "d")
				delta_y = 1;
			else
				return rotate(s);
		}
		delta_x *= speed;
		delta_y *= speed;
		xPos += delta_x;
		yPos += delta_y;
		sprite.move(delta_x, delta_y);
	}

};
