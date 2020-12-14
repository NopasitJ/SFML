#ifndef ITEM_H
#define ITEM_H

#include<SFML/Graphics.hpp>

class Item
{
private:
	
	sf::Texture healer;
	sf::RectangleShape shape;
	sf::Sprite heal;
	float dropSpeed;
	float dropPosition;
	int healing;
	int hp;
	int hpMax;
	void initVariable();
	void initTexture();
	void initItem();

public:
	Item(float pos_x, float pos_y);
	virtual ~Item();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getHealing() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
	
};

#endif ITEM_H

