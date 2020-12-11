#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include <Windows.h>

class Game
{
private:
	//Window
	sf::RenderWindow* window2;
	
	sf::RenderWindow* window;






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

	//Private functions
	
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	

	void initPlayer();
	void initEnemies();
	



public:
	Game();
	virtual ~Game();
	bool state;

	//Functions

	//core
	void run();


	//update
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();


	//render
	void renderGUI();
	void renderWorld();
	void render();
};


