#include<SFML/Graphics.hpp>
#include"Game.h"
#include<time.h>
using namespace sf;
using namespace std;
int main()
{

    sf::RenderWindow window2(sf::VideoMode(800, 600), "WTF");
    sf::CircleShape collision(100.f);
    collision.setPosition({ 100.f,100.f });
    collision.setFillColor(sf::Color::Red);

    //menu background

    Texture btnplayTexture, backTexture,btnscoreTexture,btnexitTexture;
    RectangleShape btnplay(Vector2f(354.0f / 2, 95.0f / 1.5));
    RectangleShape sbtnplay(Vector2f(354.0f / 2 * 1.2, 95.0f / 1.5 * 1.2));
    RectangleShape btnscore(Vector2f(484.0f / 2, 97.0f / 1.5));
    RectangleShape sbtscore(Vector2f(484.0f / 2 * 1.2, 97.0f / 1.5 * 1.2));
    RectangleShape btnexit(Vector2f(354.0f / 2, 94.0f / 1.5));
    RectangleShape sbtexit(Vector2f(354.0f / 2 * 1.2, 94.0f / 1.5 * 1.2));
    RectangleShape back(Vector2f(1400.0f, 700.0f));

    btnplayTexture.loadFromFile("pic/start.png");
    btnscoreTexture.loadFromFile("pic/score.png");
    btnexitTexture.loadFromFile("pic/exit.png");
    backTexture.loadFromFile("pic/eiei.jpg");

    btnplay.setTexture(&btnplayTexture);
    sbtnplay.setTexture(&btnplayTexture);
    btnscore.setTexture(&btnscoreTexture);
    sbtscore.setTexture(&btnscoreTexture);
    btnexit.setTexture(&btnexitTexture);
    sbtexit.setTexture(&btnexitTexture);
    back.setTexture(&backTexture);



    while (1)
    {
        int state = 0;
        std::cout << state << std::endl;
        if (state == 0)
        {
            

                btnplay.setPosition(100, 150);
                sbtnplay.setPosition(100, 150);
                btnscore.setPosition(100, 250);
                sbtscore.setPosition(100, 250);
                btnexit.setPosition(100, 350);
                sbtexit.setPosition(100, 350);

                Vector2i mouse = Mouse::getPosition(window2);
                printf("mousepos x= %.0f y= %.0f\n", (float)mouse.x, (float)mouse.y);




                back.setPosition(0, 0);

                window2.clear(Color(150, 150, 150));
                //view.setCenter(player.GetPosition());

                window2.draw(back);
                if (mouse.x > 105 and mouse.x < 275 and mouse.y>150 and mouse.y < 210) {
                    window2.draw(sbtnplay);
                    window2.draw(btnscore);
                    window2.draw(btnexit);
                }
                else if(mouse.x >105 and mouse.x <340 and mouse.y >255 and mouse.y <310)
                {
                    window2.draw(btnplay);
                    window2.draw(sbtscore);
                    window2.draw(btnexit);
                }
                else if (mouse.x > 105 and mouse.x < 285 and mouse.y > 355 and mouse.y < 410)
                {
                    window2.draw(btnplay);
                    window2.draw(btnscore);
                    window2.draw(sbtexit);
                }
              
                else
                {
                    window2.draw(btnplay);
                    window2.draw(btnscore);
                    window2.draw(btnexit);
                }
            
                window2.display();


                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (mouse.x > 105 and mouse.x < 275 and mouse.y>150 and mouse.y < 210)

                        state = 1;
                    if (mouse.x > 105 and mouse.x < 285 and mouse.y > 355 and mouse.y < 410)
                    {
                        window2.close();
                        break;
                    }
                }
                
            }
            if (state == 1)
            {


                Game game;
                game.run();


            }


        }
        return 0;
    }
