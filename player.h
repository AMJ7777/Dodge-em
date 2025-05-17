/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include <SFML/Graphics.hpp>
#include<string.h>
#include "ARRAY.h"
using namespace sf;
class Position
{
	float x, y;
public:
	Position(float x = 0, float y = 0) :x(x), y(y) {}
	void setX(float x)
	{
		this->x = x;
	}
	void setY(float y)
	{
		this->y = y;
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}

};
class Player {
public:
	int score;
	Text myScore;
	Texture tex;
	Sprite sprite;
	float speed = 1;
	Position playerPos;
	int activeFace;
	ARRAY<string> trans;
	Text scoretext, livtext;
	int lives;
	string status;
	Player(){}
	Player(ARRAY<string> * trans)
	{
	
		status = "alive";
		lives = 103;
		score = 0;
		activeFace = 0;
		this->trans = *trans;
	
		// score
		scoretext.setCharacterSize(80);
		scoretext.setStyle(sf::Text::Bold);
		scoretext.setFillColor(sf::Color::Black);
		scoretext.setPosition(700, 5);
		scoretext.setString(std::to_string(score));
		// lives
		livtext.setCharacterSize(80);
		livtext.setStyle(sf::Text::Bold);
		livtext.setFillColor(sf::Color::Blue);
		livtext.setPosition(320, 5);
		livtext.setString(std::to_string(lives));
		//sprite
		tex.loadFromFile(trans->data[activeFace]);
	
		sprite.setTexture(tex);
		sprite.setPosition(300, 800); // initially x=340 ,y=700
		sprite.setScale(0.75, 0.75);
		playerPos.setX(300);
		playerPos.setY(800); 
		
	}
	void changeFace(int af)
	{
		tex.loadFromFile(trans[af]);
	}
	void setPosition(int x, int y)
	{
		playerPos.setX(x);
		playerPos.setY(y);
		sprite.setPosition(x, y);
	}
	void setLives(int newlives)
	{
		lives = newlives;
		livtext.setString(std::to_string(lives));
	}
	void setScore(int newScore) {
		score = newScore;
		scoretext.setString(std::to_string(score));
	}
	const sf::Text& getLives() {

		return livtext;
	}
	const sf::Text& getScore() {

		return scoretext;
	}
	bool boundryCheck(string trans)
	{
		if (trans == "u")
			return (playerPos.getY() > -12);
		else if (trans == "d")
			return (playerPos.getY() < 800);
		else if (trans == "l")
			return (playerPos.getX() > -25);
		else if (trans == "r")
			return (playerPos.getX() < 901);

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
	void move(std::string s) {
		float delta_x = 0, delta_y = 0;
		//	if (!boundryCheck(s))
			//	return;
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
		playerPos.setX(playerPos.getX() + delta_x);
		playerPos.setY(playerPos.getY() + delta_y);
		sprite.move(delta_x, delta_y);
	}

};
