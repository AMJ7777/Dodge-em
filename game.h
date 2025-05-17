/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;

#include "opponent.h"
# include"RedFood.h"
# include"GreenFood.h"
# include"BlueFood.h"
# include"WhiteFood.h"
#include "Food.h"

const char title[] = "Dodge Em, Fall-2023";
using namespace sf;
class Line
{
public:
	RectangleShape shape;
	Line()
	{

	}
	Line(float x, float y, float width, float height, sf::Color color = Color::Black)
	{
		shape.setSize(Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(color);
	}
};
class Box
{
public:
	RectangleShape shape;
	int direction; // Direction of movement for the box

	Box(float x, float y, float width, float height, int initialDirection)
		: direction(initialDirection)
	{
		shape.setSize(Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(Color::Red); // Adjust the color as needed
	}

	void move(float speed, float offsetY)
	{
		shape.move(speed * direction, offsetY);
	}
};
class Game
{
public:
	int pause;
	Sprite background; //Game background sprite
	Texture bg_texture;
	Player* p; //player 
	Opponent* o;

	ARRAY<Line>mazeLine;
	ARRAY<RedFood> redfood;
	ARRAY<GreenFood> greenfood;
	ARRAY<BlueFood> bluefood;
	ARRAY<WhiteFood>whitefood;
	Text Message;
	Font font;
	int currentLevel;
	bool eatenBlue;
	bool eatenWhite;
	int pick;
	int pick1;
	// Score of all Levels;
	Game()
	{
		
		p = new Player(new ARRAY<string>( "img/car1_t1.png", "img/car1_t2.png", "img/car1_t3.png", "img/car1_t4.png" ));
	
		o = new Opponent(new ARRAY<string>("img/car2_t1.png", "img/car2_t2.png", "img/car2_t3().png", "img/car2_t4.png"));
	
		// background
		bg_texture.loadFromFile("img/background3.jpg");
		background.setTexture(bg_texture);
		background.setScale(2, 1.5);
		// EndMessage
		Message.setCharacterSize(80);
		Message.setStyle(sf::Text::Bold);
		Message.setFillColor(sf::Color::Blue);
		Message.setPosition(230, 350);

		// score and lives 
		font.loadFromFile("Arial.ttf");
		currentLevel = 1;
		//	initializeSmallBoxes();
		drawMaze();
		placeFood1();
		eatenBlue = false;
		eatenWhite = false;
		pick = 0;
		pick1 = 1;
	}

	template <typename T>
	bool collisionCheck(string direction, sf::FloatRect characterStart,  ARRAY<T> * shapes, float speed = 0) {
		speed = p->speed;
		sf::FloatRect characterEnd = characterStart;

		if (direction == "r")
			characterEnd.left += speed; // Move right by 'distance'
		else if (direction == "l")
			characterEnd.left -= speed; // Move left by 'distance'
		else if (direction == "u")
			characterEnd.top -= speed; // Move up by 'distance'
		else if (direction == "d")
			characterEnd.top += speed; // Move down by 'distance'

		for (int i = 0; i < shapes->get_size();i++) {
			sf::FloatRect shapeBounds = shapes->data[i].shape.getGlobalBounds();
			sf::FloatRect sweptBounds = characterStart;

			if (direction == "r") {
				sweptBounds.width = characterEnd.left + characterEnd.width - sweptBounds.left;
				if (sweptBounds.intersects(shapeBounds))
					return true;
			}
			else if (direction == "l") {
				sweptBounds.left = std::min(characterStart.left, characterEnd.left);
				sweptBounds.width = characterStart.left - sweptBounds.left + std::max(characterStart.width, characterEnd.width);
				if (sweptBounds.intersects(shapeBounds)) {
					return true;
				}
			}
			else if (direction == "u") {
				sweptBounds.top = std::min(characterStart.top, characterEnd.top);
				sweptBounds.height = characterStart.top - sweptBounds.top + std::max(characterStart.height, characterEnd.height);
				if (sweptBounds.intersects(shapeBounds)) {
					return true;
				}
			}
			else if (direction == "d") {
				sweptBounds.height = characterEnd.top + characterEnd.height - sweptBounds.top;
				if (sweptBounds.intersects(shapeBounds)) {
					return true;
				}
			}
		}
		return false;
	}
	void placeFood1()
	{

		int x = 67, y = 50;
		for (int i = 0; i < 8; i++)
		{
			y += 100;
			x = 67;
			for (int j = 0; j < 4; j++)
			{
				if (i == j || i == j + 4)
					greenfood.emplace_back(x, y);
				else
					redfood.emplace_back(x, y);
				x += 120;
			}
		}
		x = 780, y = 50;
		for (int i = 0; i < 8; i++)
		{
			y += 100;
			x = 780;
			for (int j = 0; j < 4; j++)
			{
				if (i == j || i == j + 4)
					greenfood.emplace_back(x, y);
				else
					redfood.emplace_back(x, y);
				x += 120;
			}
		}

	}
	void placeFood3()
	{
		int x = 67, y = 50;
		for (int i = 0; i < 8; i++)
		{
			y += 100;
			x = 67;
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
				{

					whitefood.emplace_back(x, y);
				}
				else
				{
					greenfood.emplace_back(x, y);
				}
				x += 120;
			}
		}
		x = 780, y = 50;
		for (int i = 0; i < 8; i++)
		{
			y += 100;
			x = 780;
			for (int j = 0; j < 4; j++)
			{
				if (i == j + 4)
				{
					whitefood.emplace_back(x, y);
				}
				else
				{
					greenfood.emplace_back(x, y);
				}
				x += 120;
			}
		}
	}
	void drawMaze()
	{
		// boundry
		mazeLine.emplace_back(0, 2, 1200, 3, Color::Yellow);
		mazeLine.emplace_back(2, 0, 3, 1000, Color::Yellow);
		mazeLine.emplace_back(2, 895, 1200, 3, Color::Yellow);
		mazeLine.emplace_back(1195, 2, 3, 1000, Color::Yellow);

		int wFactor = 400;
		int lFactor = 5;
		int inX = 20, inY = 90;
		int factor = 100;
		int sqCount = 4;
		for (int i = 0; i < sqCount; i++)
		{
			mazeLine.emplace_back(5 + inX, 5 + inY, wFactor, lFactor); //(width,length)   (x,y)
			mazeLine.emplace_back(5 + inX, 5 + inY, lFactor, wFactor); //(width,length)
			inX += 130;
			inY += 100;
			wFactor -= 100;
		}
		inX = 765;
		inY = 90;
		wFactor = 400;
		lFactor = 5;

		for (int i = 0; i < sqCount; i++)
		{
			mazeLine.emplace_back(5 + inX, 5 + inY, wFactor, lFactor); //(width,length)
			mazeLine.emplace_back(5 + inX + wFactor, 5 + inY, lFactor, wFactor); //(width,length)
			inY += 100;
			wFactor -= 100;
		}
		inX = 20;
		inY = 530;
		lFactor = 350;
		wFactor = 5;

		for (int i = 0; i < sqCount; i++)
		{
			mazeLine.emplace_back(5 + inX, 5 + inY, wFactor, lFactor); //(width,length) (x,y)
			mazeLine.emplace_back(5 + inX, 5 + inY + lFactor, lFactor, wFactor); //(width,length)   
			inX += 130;
			lFactor -= 100;
		}
		inX = 1165;
		inY = 530;
		lFactor = 350;
		wFactor = 5;

		for (int i = 0; i < sqCount; i++)
		{
			mazeLine.emplace_back(5 + inX, 5 + inY, wFactor, lFactor); //(width,length) (x,y)

			mazeLine.emplace_back(5 + inX - lFactor, 5 + inY + lFactor, lFactor, wFactor); //(width,length)  
			inX -= 100;
			lFactor -= 100;
		}
	}

	bool isdead()
	{
		if (eatenWhite)
			return false;

		return  (p->sprite.getGlobalBounds().intersects(o->sprite.getGlobalBounds()));
	}
	void endGame(RenderWindow& window)
	{

		window.clear(Color::Black);
		Message.setString("Try Again Champ !");
		Message.setFont(font);
		window.draw(Message);

		window.display();
		while (window.isOpen()) {
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				window.close();

		}

	}
	void pointsCheck(float& timer1, float& timer2)
	{
		for (size_t i = 0; i < redfood.get_size();) {
			if (redfood[i].shape.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
				p->setScore(p->score + 10);
				redfood.erase(i); // Erase the element at index i
			}
			else {
				++i;
			}
		}



		//for (auto it = redfood.begin(); it != redfood.end();) {
		//	if (it->shape.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
		//		p->setScore(p->score + 10);
		//		it = redfood.erase(it); // Erase the element and get the new iterator
		//		return;
		//	}
		//	else {
		//		++it;
		//	}
		//}

		for (size_t i = 0; i < greenfood.get_size();) {
			if (greenfood[i].shape.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
				p->setScore(p->score + 20);
				greenfood.erase(i); // Erase the element at index i
			}

			else
			{
				i++;

			}

		}



		//for (int it = 0 ; it != greenfood.end();) {
		//	if (it->shape.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
		//		p->setScore(p->score + 20);
		//		 greenfood[i].erase(it); // Erase the element and get the new iterator
		//		return;
		//	}
		//	else {

		//	}
		//}
		// 

		for (int it = 0; it < bluefood.get_size();) {
			if (bluefood[it].shape.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
				p->setScore(p->score + 10);
				/*p->speed = p->speed * 1.5; */   
				// increase speed 1.5x
				timer1 = 1.0f;
				eatenWhite = true;
				bluefood.erase(it); // Erase the element and get the new iterator
				return;
			}
			else {
				++it;
			}
		}


	
		for (int it = 0 ; it < whitefood.get_size();) {
			if (whitefood[it].shape.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {
				if (timer2 < 0)
					timer2 = 0;
				timer2 += 3.0f;
				eatenWhite = true;
			 whitefood.erase(it); // Erase the element and get the new iterator
				return;
			}
			else {
				++it;
			}
		}

	}
	void oppoMovement_2(static string& opponentMovment)
	{
		if (opponentMovment == "r" && collisionCheck("r", o->sprite.getGlobalBounds(), &mazeLine))
			opponentMovment = "u";
		else if (opponentMovment == "u" && collisionCheck("u", o->sprite.getGlobalBounds(), &mazeLine))
			opponentMovment = "l";
		else if (opponentMovment == "l" && collisionCheck("l", o->sprite.getGlobalBounds(), &mazeLine))
			opponentMovment = "d";
		else if (opponentMovment == "d" && collisionCheck("d", o->sprite.getGlobalBounds(), &mazeLine))
			opponentMovment = "r";
		o->move(opponentMovment);
	}


	void oppoMovment_1(static string& opponentMovmentOne)
	{
		if (opponentMovmentOne == "l" && collisionCheck("l", o->sprite.getGlobalBounds(), &mazeLine))
			opponentMovmentOne = "r";
		else if (opponentMovmentOne == "r" && collisionCheck("r", o->sprite.getGlobalBounds(), &mazeLine))
			opponentMovmentOne = "l";
		o->move(opponentMovmentOne);
	}
	void drawFood1(RenderWindow& window)
	{

	
		for (size_t i = 0; i < redfood.get_size(); i++) {
		
			window.draw(redfood[i].shape);
		}

		for (size_t i = 0; i < greenfood.get_size(); i++) {

			window.draw(greenfood[i].shape);

		}
	
	}
	void levelChange(int newLevel, RenderWindow& window)
	{
		currentLevel = newLevel;
		window.clear(Color::Black);
		Message.setString("Level" + to_string(newLevel - 1) + "Passed !");
		Message.setFont(font);
		window.draw(Message);
		window.display();
		while (1) {
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				break;

		}
		if (currentLevel == 2)
			placeFood2();
		if (currentLevel == 3)
			placeFood3();


	}
	void placeFood2()
	{
		int x = 67, y = 50;
		for (int i = 0; i < 8; i++)
		{
			y += 100;
			x = 67;
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					bluefood.emplace_back(x, y);
				else
					redfood.emplace_back(x, y);
				x += 120;
			}
		}
		x = 780, y = 50;
		for (int i = 0; i < 8; i++)
		{
			y += 100;
			x = 780;
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					bluefood.emplace_back(x, y);
				else
					redfood.emplace_back(x, y);
				x += 120;
			}
		}
	}
	void drawFood2(RenderWindow& window)
	{

		for (size_t i = 0; i < bluefood.get_size(); i++) {

			window.draw(bluefood[i].shape);
		}
		

	/*	for (auto& it : redfood)
			window.draw(it.shape);*/

		for (size_t i = 0; i < redfood.get_size(); i++) {
		
			window.draw(redfood[i].shape);
		}
	}
	void drawFood3(RenderWindow& window)
	{
	/*	for (auto& it : greenfood)
			window.draw(it.shape);*/
		for (size_t i = 0; i < greenfood.get_size(); i++) {

			window.draw(greenfood[i].shape);

		}
		

		for (size_t i = 0; i < whitefood.get_size(); i++) {

			window.draw(whitefood[i].shape);


		}
	}
	void start_game(bool& restart, string playerName)
	{
		int choice = 0;
		bool end_game = false;
		static string playerMovment = "l";
		static string opponentMovment = "r";
		srand(time(0));
		RenderWindow window(VideoMode(1200, 900), title);
		Clock clock;
		float timer1, timer2 = 0;
		float t;
		Texture ps;
		Sprite Pause;
		ps.loadFromFile("img/pause.png");
		Pause.setTexture(ps);
		RenderWindow pause;
		while (window.isOpen())
		{
			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed) // If cross/close is clicked/pressed
					window.close(); //close the game                        	    
			}

			if (Keyboard::isKeyPressed(Keyboard::Left) && (!collisionCheck("l", p->sprite.getGlobalBounds(), &mazeLine)))
				playerMovment = "l";
			if (Keyboard::isKeyPressed(Keyboard::Right) && (!collisionCheck("r", p->sprite.getGlobalBounds(), &mazeLine)))
				playerMovment = "r";
			if (Keyboard::isKeyPressed(Keyboard::Up) && (!collisionCheck("u", p->sprite.getGlobalBounds(), &mazeLine)))
				playerMovment = "u";
			if (Keyboard::isKeyPressed(Keyboard::Down) && (!collisionCheck("d", p->sprite.getGlobalBounds(), &mazeLine)))
				playerMovment = "d";
			//playerMove
			/*
			* if head collison right
			* if right collision down
			* if down collision left
			* if left collision up
			*
			*/
			{
				if (playerMovment == "u" && collisionCheck("u", p->sprite.getGlobalBounds(), &mazeLine))
					playerMovment = "r";
				else if (playerMovment == "r" && collisionCheck("r", p->sprite.getGlobalBounds(), &mazeLine))
					playerMovment = "d";
				else if (playerMovment == "d" && collisionCheck("d", p->sprite.getGlobalBounds(), &mazeLine))
					playerMovment = "l";
				if (playerMovment == "l" && collisionCheck("l", p->sprite.getGlobalBounds(), &mazeLine))
					playerMovment = "u";
				p->move(playerMovment);

			}
			//levelOne Movment of Opponent
			if (currentLevel == 1)
				oppoMovment_1(opponentMovment);
			if (currentLevel == 2 || currentLevel == 3)
			{
				oppoMovement_2(opponentMovment);
				/*
				srand(time(0));
				choice = rand() % 4;
				if (choice == 0 && !collisionCheck("u", o->sprite.getGlobalBounds(), mazeLine))
					opponentMovment = "u";
				else if (choice == 1 && !collisionCheck("d", o->sprite.getGlobalBounds(), mazeLine))
					opponentMovment = "d";
				else if (choice == 2 && !collisionCheck("l", o->sprite.getGlobalBounds(), mazeLine))
					opponentMovment = "l";
				else if (!collisionCheck("r", o->sprite.getGlobalBounds(), mazeLine))
					opponentMovment = "r";
					*/

			}

			/*
			if (opponentMovmentOne == "l" && collisionCheck("l", o->sprite.getGlobalBounds(), mazeLine))
				opponentMovmentOne = "r";
			else if (opponentMovmentOne == "r" && collisionCheck("r", o->sprite.getGlobalBounds(), mazeLine))
				opponentMovmentOne = "l";
			o->move(opponentMovmentOne);
			*/

			// checking for Points
			pointsCheck(timer1, timer2);
			t = clock.restart().asSeconds();
			timer1 -= t;
			timer2 -= t;
			if (eatenBlue == true && timer1 <= 0.0f)
			{
				p->speed = 1;
				eatenBlue = false;
			}
			if (eatenWhite && timer2 <= 0.0f)
			{
				eatenWhite = false;
			}

			if (p->score >= 800 && currentLevel == 1)
				levelChange(2, window);
			if (p->score >= 1440 && currentLevel == 2)
				levelChange(3, window);
			// checking for player opponent Collision
			if (isdead())
			{

				if (p->lives == 1)
					endGame(window);
				//window.clear(); //clears the scree
				// restore original coordinates of players
				p->setPosition(300, 800);
				o->setPosition(500, 800);
				p->setLives(p->lives - 1);
				p->status = "dead";
				p->changeFace(1);

				opponentMovment = "r";
				playerMovment = "l";
			}
			///////////////////////////////////////////////////////
			if (Keyboard::isKeyPressed(Keyboard::Escape)) // If down key is pressed
			{
				bool exit = false;
				bool resume = false;
				Font pausefont;
				pausefont.loadFromFile("Fonts/1.ttf");
				Text textpause;
				textpause.setFont(font);
				textpause.setCharacterSize(60);
				textpause.setFillColor(Color::White);
				textpause.setPosition(550, 100);
				textpause.setString("Paused");
				pause.create(VideoMode(1200, 900), "Pause Window");

				while (pause.isOpen())
				{
					Event pc;
					while (pause.pollEvent(pc)) // Event is occurring - until the game is in running state
					{
						/*if (Mouse::getPosition().y > 720 && Mouse::getPosition().y < 780)
						{
							if (Mouse::getPosition().x > 840 && Mouse::getPosition().x < 1115)
								if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
								{
									exit = true;
								}
						}
						if (Mouse::getPosition().y > 600 && Mouse::getPosition().y < 665)
						{
							if (Mouse::getPosition().x > 840 && Mouse::getPosition().x < 1115)
								if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
								{
									pause.close();
								}
						}
						if (Mouse::getPosition().y > 500 && Mouse::getPosition().y < 560)
						{
							if (Mouse::getPosition().x > 840 && Mouse::getPosition().x < 1115)
								if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
								{

									resume = true;
								}
						}*/
						if (Keyboard::isKeyPressed(Keyboard::R))
						{
							resume = true;
						}
						if (Keyboard::isKeyPressed(Keyboard::E))
						{
							exit = true;
							end_game = true;
						}
						if (Keyboard::isKeyPressed(Keyboard::I))
						{
							display_Instructions();
						}
						if (Keyboard::isKeyPressed(Keyboard::H))
						{
							displayHighScore();
						}

						if (Keyboard::isKeyPressed(Keyboard::L))
						{
							end_game = true;
							restart = true;
							pause.close();
						}
						if (pc.type == Event::Closed) // If cross/close is clicked/pressed
							pause.close();
						if (resume)
						{
							pause.close();
						}
						if (exit)
						{
							end_game = true;
							pause.close();
						}
						if (end_game) //file handling
						{

							bool found = true;
							ifstream file("score.txt");
							ofstream tout("temp.txt");
							int x = 0;
							int in;
							string line;
							while (getline(file, line))
							{
								if (!line.empty())
								{
									getline(file, line);
									x++;
								}
							}
							file.close();
							file.open("score.txt");

							for (int i = 0; i < x; i++)
							{
								int j;
								string name;
								file >> j;
								file >> name;
								if (p->score > j && found)
								{
									tout << p->score << endl;
									tout << playerName << endl;
									found = false;
								}
								tout << j << endl;
								tout << name << endl;
							}
							if (found)
							{
								tout << p->score << endl;
								tout << playerName << endl;
							}

							file.close();
							tout.close();
							remove("score.txt");
							rename("temp.txt", "score.txt");
							window.close();
						}
					}
					pause.draw(Pause);
					pause.display();

				}
			}
			///////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////
			window.draw(background);
			p->scoretext.setFont(font);
			window.draw(p->getScore());

			p->livtext.setFont(font);
			window.draw(p->getLives());

			window.draw(p->sprite);
			if (!eatenWhite)
				window.draw(o->sprite);
			// drawMaze
			for (int i =0; i < mazeLine.get_size() ;i++)
				window.draw(mazeLine[i].shape);
			if (currentLevel == 1)
				drawFood1(window);
			if (currentLevel == 2)
				drawFood2(window);
			if (currentLevel == 3)
				drawFood3(window);
			window.display();  //Displying all the sprites

			while (p->status == "dead")
			{
				if (Keyboard::isKeyPressed(Keyboard::Enter))
					p->status = "alive";
			}
		}


	}


	void display_Instructions()
	{
		Image cursorImage;
		cursorImage.loadFromFile("img1/PNG/UI/cursor.png");
		Cursor cursor;
		cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0, 0 });
		RenderWindow Inst(VideoMode(1200, 900), "Instructions");
		Inst.setMouseCursor(cursor);
		bool stop = false;
		Sprite background;
		Texture btexture;
		btexture.loadFromFile("img/instructions.png");
		background.setTexture(btexture);
		while (Inst.isOpen())
		{
			Event e;
			while (Inst.pollEvent(e))
			{

				if (Keyboard::isKeyPressed(Keyboard::Key::X))
				{
					stop = true;
				}
				if (e.type == Event::Closed)
					Inst.close();
				if (stop)
				{
					stop = false;
					return;
				}
			}
			Inst.draw(background);
			Inst.display();
		}
	}
	void displayHighScore()
	{

		RenderWindow high(VideoMode(1200, 900), "High Score");
		Font font;
		font.loadFromFile("Fonts/1.ttf");
		Text name1;
		Text name2;
		Text name3;
		Text score1;
		Text score2;
		Text score3;
		name1.setFont(font);
		name2.setFont(font);
		name3.setFont(font);
		Sprite background;
		Texture btexture;
		btexture.loadFromFile("img/highscores.png");
		background.setTexture(btexture);
		score1.setFont(font);
		score2.setFont(font);
		score3.setFont(font);

		ifstream file("score.txt");
		string n[3];
		int score[3];
		for (int i = 0; i < 3; i++)
		{
			file >> score[i];
			file >> n[i];
		}
		name1.setString(n[0]);
		name2.setString(n[1]);
		name3.setString(n[2]);
		score1.setString(to_string(score[0]));
		score2.setString(to_string(score[1]));
		score3.setString(to_string(score[2]));
		name1.setFillColor(Color::Black);
		name2.setFillColor(Color::Black);
		name3.setFillColor(Color::Black);
		name1.setPosition(270, 450);
		name2.setPosition(270, 530);
		name3.setPosition(270, 610);
		score1.setFillColor(Color::Red);
		score2.setFillColor(Color::Red);
		score3.setFillColor(Color::Red);
		score1.setPosition(860, 450);
		score2.setPosition(860, 530);
		score3.setPosition(860, 610);
		bool stop = false;
		while (high.isOpen())
		{
			// cout << Mouse::getPosition().x << " " << Mouse::getPosition().y << endl;
			Event e;
			while (high.pollEvent(e))
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::X))
				{
					stop = true;
				}
				if (e.type == Event::Closed)
					high.close();
				if (stop)
				{
					stop = false;
					return;
				}
			}
			high.draw(background);
			high.draw(name1);
			high.draw(name2);
			high.draw(name3);
			high.draw(score3);
			high.draw(score2);
			high.draw(score1);
			high.display();
		}
	}
};