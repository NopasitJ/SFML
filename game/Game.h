#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include <Windows.h>
#include<SFML/Audio.hpp>
#include"Item.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window2;
	
	sf::RenderWindow* window;

	//sound
	sf::SoundBuffer soundeffect;
	sf::Sound shooteffect;
	sf::Music music;



	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//item
	float itemsp;
	float itemspMax;
	std::vector<Item*>items;
	std::vector<sf::Vector2f> itemPos;
	std::vector<sf::Clock> itemTime;
	//Private functions
	
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initSound();

	void initPlayer();
	void initEnemies();
	void initItem();
	
	//return points

	
	
	



public:
	Game();
	virtual ~Game();
	bool state;
	int rtScore;
	//Functions

	//core
	void run();

int point;
	//update
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateItem();
	void updateCombat();
	void update();


	//render
	void renderGUI();
	void renderWorld();
	void render();
};


