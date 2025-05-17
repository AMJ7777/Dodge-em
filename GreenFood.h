/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include <SFML/Graphics.hpp>
#include "Food.h"
class GreenFood : public Food
{
public:
	sf::CircleShape shape;


	GreenFood(float x = 0, float y = 0, float radius = 10) {
		shape.setRadius(radius);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Green); // Set the color to green
	}

	virtual void display()
	{
		cout << "Green Food";
		cout << x << y;


	}
};
