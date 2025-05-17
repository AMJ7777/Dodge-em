/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include "Food.h"

class WhiteFood: public Food
{
public:

	CircleShape shape;

	WhiteFood(float x = 0, float y = 0, float radius = 10)
	{
		shape.setRadius(radius);
		shape.setPointCount(3);
		shape.setPosition(x, y);
		shape.setFillColor(Color::White); // Adjust the color as needed
	}

	virtual void display()
	{
		cout << "White Food";
		cout << x << y;


	}
};