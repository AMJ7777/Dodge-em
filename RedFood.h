/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include <SFML/Graphics.hpp>
#include "Food.h"
class RedFood : public Food
{
public:
	RectangleShape shape;
	RedFood()
	{

	}
	RedFood(float x, float y, float width = 20, float height = 20)
	{
		shape.setSize(Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(Color::Red); // Adjust the color as needed
	}


	virtual void display()
	{
		cout << "Red Food";
		cout << x << y;

	}
};