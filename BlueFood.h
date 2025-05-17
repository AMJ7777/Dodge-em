/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include <SFML/Graphics.hpp>
#include "Food.h"

class BlueFood: public Food

{
public:

	CircleShape shape;

	BlueFood(float x = 0, float y = 0, float radius = 10)
	{
		shape.setRadius(radius);
		shape.setPointCount(5);
		shape.setPosition(x, y);
		shape.setFillColor(Color::Blue); // Adjust the color as needed
	}

	virtual void display()
	{
		cout << "Blue Food";
		cout << x << y;



	}
};