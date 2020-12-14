#include "Item.h"
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
void Item::initVariable()
{
	this->hp = this->hpMax;
	this->healing = this->hp + 5;
}

void Item::initTexture()
{
	if (!healer.loadFromFile("pic/potion.png"))
	{
		cout << "load heal item failed" << endl;
	}
}

void Item::initItem()
{
	this->heal.setTexture(this->healer);

	this->heal.setPosition(0,0);
}

Item::Item(float pos_x, float pos_y)
{
	this->initVariable();
	this->initTexture();

	this->heal.setPosition(0, 0);
}

Item::~Item()
{

}
//Accessors
const sf::FloatRect Item::getBounds() const
{
	return this->heal.getGlobalBounds();
}

const int& Item::getHealing() const
{
	return this->healing;
}


//Functions
void Item::update()
{
	this->heal.move(0.f, this->dropSpeed);
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->heal);
}
