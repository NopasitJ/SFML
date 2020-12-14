#define _CRT_SECURE_NO_WARNINGS
#include<SFML/Graphics.hpp>
#include"Game.h"
#include"Textbox.h"
#include<time.h>
#include<string>
#include<SFML/Audio.hpp>
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace sf;
using namespace std;

bool comp(const pair<int, string>& a, const pair<int, string>& b)
   
{
    return (a.first > b.first);
}

//high score function
void showHighScore(int x, int y, string word, sf::RenderWindow& window2, sf::Font* font)
{
    sf::Text text;
    text.setFont(*font);
    text.setPosition(x, y);
    text.setString(word);
    if (word == "HIGHSCORE")
        text.setCharacterSize(40);
    else
        text.setCharacterSize(20);
        window2.draw(text);

}

int main()
{
    Event event;
  
    string sname = "unknown";
    int sscore = 0;
    
    Font font;

    int score[6] = {};
    string name[6] = {};
    char temp[255] = {};

    vector <pair<int, string>> userScore;
    FILE* fp;
    // high score
    {
        font.loadFromFile("fonts/HELLO.ttf");
        fp = fopen("states/Score.txt", "r");
        for (int i = 0; i < 5; i++)
        {
            fscanf(fp, "%s", &temp);
            name[i] = temp;
            fscanf(fp, "%d", &score[i]);
           
            userScore.push_back(make_pair(score[i], name[i]));
            cout << temp << " " << score;
        }
        sort(userScore.begin(), userScore.end(),comp);

       
        fclose(fp);
    }
     
    //playernametextbox
    Textbox playername(20, sf::Color::White, true);
    playername.setFont(font);
    playername.setPosition({ 400.0,550.0f });
    playername.setlimit(true, 10);
    //start game
    sf::RenderWindow window2(sf::VideoMode(800, 600), "WTF");
    
  
    //menu background

    Texture btnplayTexture, backTexture, btnscoreTexture, btnexitTexture;
    Texture returnTexture, enterTexture;

    RectangleShape btnplay(Vector2f(354.0f / 2, 95.0f / 1.5));
    RectangleShape sbtnplay(Vector2f(354.0f / 2 * 1.2, 95.0f / 1.5 * 1.2));
    RectangleShape btnscore(Vector2f(484.0f / 2, 97.0f / 1.5));
    RectangleShape sbtscore(Vector2f(484.0f / 2 * 1.2, 97.0f / 1.5 * 1.2));
    RectangleShape btnexit(Vector2f(354.0f / 2, 94.0f / 1.5));
    RectangleShape sbtexit(Vector2f(354.0f / 2 * 1.2, 94.0f / 1.5 * 1.2));
    RectangleShape back(Vector2f(1400.0f, 700.0f));
    RectangleShape btnreturn(Vector2f(556.0f / 8, 572.0f / 10)), sbtnreturn(Vector2f(556.0f / 8 * 1.2, 572.0f / 10 * 1.2));
    RectangleShape btnenter(Vector2f(822.0f / 5, 69.0f / 5));
    //load pic
    btnplayTexture.loadFromFile("pic/start.png");
    btnscoreTexture.loadFromFile("pic/score.png");
    btnexitTexture.loadFromFile("pic/exit.png");
    backTexture.loadFromFile("pic/eiei.jpg");
    returnTexture.loadFromFile("pic/return.png");
    enterTexture.loadFromFile("pic/Enter.png");
    
    btnplay.setTexture(&btnplayTexture);
    sbtnplay.setTexture(&btnplayTexture);
    btnscore.setTexture(&btnscoreTexture);
    sbtscore.setTexture(&btnscoreTexture);
    btnexit.setTexture(&btnexitTexture);
    sbtexit.setTexture(&btnexitTexture);
    back.setTexture(&backTexture);
    btnreturn.setTexture(&returnTexture);
    sbtnreturn.setTexture(&returnTexture);
    btnenter.setTexture(&enterTexture);
    //sound
    sf::SoundBuffer mainmenuSound;
    if (!mainmenuSound.loadFromFile("sound/PUBG.ogg"))
    {
        cout << "cant open music" << endl;
    }
    sf::Sound mainmenuSong;
    mainmenuSong.setLoop(true);
    mainmenuSong.setBuffer(mainmenuSound);
    //mainmenuSong.play();
    int state = 0;
    while (1)
    {
      cout << userScore.size();
        //std::cout << state << std::endl;
        //// highscore
       
        if (state == -1)
        {
            window2.clear(Color(150, 150, 150));
            window2.draw(back);
            Vector2i mouse = Mouse::getPosition(window2);

            cout <<"mx = "<< mouse.x << "my = " << mouse.y<<endl;
            


            showHighScore(550, 150 - 20, "HIGHSCORE", window2, &font);
            
            for (int i = 0; i < 5; i++)
            {

                showHighScore(120, 190 + (1+  i) * 60, userScore[i].second, window2, &font);
                showHighScore(700, 190 + (1+  i) * 60, to_string(userScore[i].first), window2, &font);
            }

            if (mouse.x > 0 and mouse.x < 60 and mouse.y>0 and mouse.y < 100)
                window2.draw(sbtnreturn);
            else
                window2.draw(btnreturn);


            window2.display();

            if (mouse.x > 0 and mouse.x < 60 and mouse.y>0 and mouse.y < 100)
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    state = 0;
        }
            if (state == 0)
            {
                mainmenuSong.play();
                while (window2.pollEvent(event))
                {
                    switch (event.type)
                    {
                    case Event::Closed:
                        window2.close();
                        break;

                    case sf::Event::TextEntered:
                        playername.typeOn(event);

                        
                    }
                }
                

                btnplay.setPosition(100, 150);
                sbtnplay.setPosition(100, 150);
                btnscore.setPosition(100, 250);
                sbtscore.setPosition(100, 250);
                btnexit.setPosition(100, 350);
                sbtexit.setPosition(100, 350);
                btnenter.setPosition(200,555);

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
                    window2.draw(btnenter);
                }
                else if (mouse.x > 105 and mouse.x < 340 and mouse.y >255 and mouse.y < 310)
                {
                    window2.draw(btnplay);
                    window2.draw(sbtscore);
                    window2.draw(btnexit);
                    window2.draw(btnenter);
                }
                else if (mouse.x > 105 and mouse.x < 285 and mouse.y > 355 and mouse.y < 410)
                {
                    window2.draw(btnplay);
                    window2.draw(btnscore);
                    window2.draw(sbtexit);
                    window2.draw(btnenter);
                }

                else
                {
                    window2.draw(btnplay);
                    window2.draw(btnscore);
                    window2.draw(btnexit);
                    window2.draw(btnenter);
                }
                playername.drawTo(window2);
                window2.display();


                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (mouse.x > 105 and mouse.x < 275 and mouse.y>150 and mouse.y < 210)
                    {
                        state = 1;
                        sname = playername.gettext();
                        if (sname == "\0")sname = "Unknown";
                    }
                    if (mouse.x > 105 and mouse.x < 285 and mouse.y > 355 and mouse.y < 410)
                    {
                        window2.close();
                        break;
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if ((mouse.x > 105 and mouse.x < 340 and mouse.y >255 and mouse.y < 310))
                        state = -1;
                    if ((mouse.x > 105 and mouse.x < 285 and mouse.y >355 and mouse.y < 410))
                    {
                        window2.close();
                        break;
                    }
                }
                //window2.close();

            }
            if (state == 1)
            {
                mainmenuSong.pause();

                Game game;
                game.run();

                sscore = game.point;
               


                userScore.push_back(make_pair(sscore, sname));

                sort(userScore.begin(), userScore.end() ,comp);


               
                fp = fopen("states/Score.txt", "w");
                for (int i = 0 ; i <5 ; i++)
                {
                    
                    strcpy(temp, userScore[i].second.c_str());
                    fprintf(fp, "%s %d\n", temp, userScore[i].first);
                }
                fclose(fp);
                state = 0;


            }
           


        }
        return 0;
    }

