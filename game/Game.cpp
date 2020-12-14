#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;


//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Piw Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}


void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	RectangleShape _bullet(Vector2f(20.0f, 100.0f));
	Texture _bulletload;
	_bulletload.loadFromFile("pic/charmander.png");
	_bullet.setTexture(&_bulletload);


	
	this->textures["BULLET"]->loadFromFile("pic/bullet5.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/HELLO.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(680.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(25);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	this->worldBackgroundTex.loadFromFile("pic/unnamed.jpg");
	

	this->worldBackground.setTexture(this->worldBackgroundTex);
	this->worldBackground.scale(1.7f,2.2f);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initSound()
{
	this->music.openFromFile("sound/PUBG.ogg");
	this->music.setVolume(25);

	this->music.play();
	this->music.setLoop(true);
	if (!this->soundeffect.loadFromFile("sound/drow.ogg"))
		throw"ERROR::GAME::FAILED_TO_LOAD_SOUND_EFFECT";

	this->shooteffect.setBuffer(this->soundeffect);
	this->shooteffect.setVolume(50);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initItem()
{
	this->items.push_back(new Item(500, 400));
}








//Con/Des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		
		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape){
			state = 0;
			this->window->close();
		
		}
	}
}

void Game::updateInput()
{
	//Move player
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-3.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(3.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -3.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 3.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->shooteffect.play();
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
		this->player->getPos().x + this->player->getBounds().width * 10 / 29.f,
		this->player->getPos().y - this->player->getBounds().height * 10 / 125.f,0.f, -1.f, 5.f));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->canAttack())
	{
		this->shooteffect.play();
		this->bullets.push_back(new Bullet(this->textures["BULLET"],

			this->player->getPos().x + this->player->getBounds().width -15.f,
			

			this->player->getPos().y - this->player->getBounds().height * 10 / 125.f, 0.f, -1.f, 5.f));

		this->bullets.push_back(new Bullet(this->textures["BULLET"],

			
			this->player->getPos().x + this->player->getBounds().width -100.f,

			this->player->getPos().y - this->player->getBounds().height * 10 / 125.f, 0.f, -1.f, 5.f));

	}


}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;


	point = this->points;

	std::cout << point << std::endl;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < -13.f)
	{
		this->player->setPosition(-13.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x + 80.f)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width+70 , this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		
		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}



void Game::updateItem()
{

	//Spawning
	if (this->itemsp >= this->itemspMax)
	{
		this->items.push_back(new Item(0,0));
		this->itemsp = 10.0f;
	}

	//Update
	unsigned count = 0;
	for (auto* item : this->items)
	{
		item->update();

		//Bullet culling (top of screen)
		if (item->getBounds().top > this->window->getSize().y)
		{
		//Delete item
			delete this->items.at(count);
			this->items.erase(this->items.begin() + count);
		}
		//item player collision
		else if (item->getBounds().intersects(this->player->getBounds()))
		{
			/*this->itemPos.push_back(sf::Vector2f(this->items[i]->getPosition().x, this->items[i]->getPosition().y));
			this->itemTime.push_back(sf::Clock());*/
			this->player->gainHp(this->items.at(count)->getHealing());
			delete this->items.at(count);
			this->items.erase(this->items.begin() + count);
		}

		++count;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateItem();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();


}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	for (auto* item : this->items)
	{
		item->render(this->window);
	}
	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}

