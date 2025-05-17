/////////////////////////////////////////////////////MuhammadAsadMehdi(22i1120)////////////////////////////////
/////////////////////////////////////////////////////MubarizHaroon(22i1104)////////////////////////////////
#include<SFML/Graphics.hpp>
#include<ostream>
#include<fstream>
#include "game.h"

class Menu {
public:

    //add menu attributes here
    Menu()
    {

        //constructors body
    }

    void display_menu()

    {

        // display menu screen here
        RenderWindow menu(VideoMode(1200, 900), "MENU");
        Sprite background;
        Texture btexture;
        btexture.loadFromFile("img/start.png");
        background.setTexture(btexture);
        bool end_game = false;
        bool strt = false, high = false, instruct = false, stop = false;
        bool restart = false;
        string name;
        Font font;
        font.loadFromFile("Fonts/1.ttf");
        bool enter = false;

        Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(Color::White);
        Text text1;
        text1.setFont(font);
        text1.setCharacterSize(35);
        text1.setFillColor(Color::White);
        text1.setPosition(200, 200);
        string playerName;
        text.setPosition(270, 400);
        text1.setString("Enter Username:");

        while (menu.isOpen())
        {

            if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
                    {
                btexture.loadFromFile("img/blank.png");
                background.setTexture(btexture);
                background.setScale(2, 2);
                        enter = true;
                    }
            if (Keyboard::isKeyPressed(Keyboard::Key::I))   
                    {
                        instruct = true;
                    }
            if (Keyboard::isKeyPressed(Keyboard::Key::H))
                    {
                        high = true;
                    }
            if (Keyboard::isKeyPressed(Keyboard::Key::X))
            {
                        stop = true;
            }

            // cout << Mouse::getPosition().x << " " << Mouse::getPosition().y << endl;
            Event e;
            while (menu.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    menu.close();
                if (enter)
                    if (e.type == sf::Event::TextEntered)
                    {
                        if (e.text.unicode < 128)
                        {
                            if (e.text.unicode == '\b' && !playerName.empty())
                            {
                                playerName.pop_back(); // Remove the last character
                            }
                            else if (e.text.unicode != '\b')
                            {
                                playerName += static_cast<char>(e.text.unicode); // Append the typed character
                            }

                            text.setString(playerName); // Update the displayed text
                        }
                    }
                if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    strt = true;
                    enter = false;
                }

                menu.draw(background);
            }

            if (strt)
            {
                strt = false;
                Game g;
                g.start_game(restart, playerName);
            }
            if (restart)
            {
                restart = false;
                Game g;
                g.start_game(restart, playerName);
            }
            if (stop)
            {
                stop = false;
                menu.close();
            }
            if (instruct)
            {
                instruct = false;
                display_Instructions();
            }
            if (high)
            {
                high = false;
                displayHighScore();
            }

            if (enter)
            {

                menu.draw(text);
                menu.draw(text1);
            }
            if(!enter)
            {
                menu.draw(background);
            }


            menu.display();
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
