#pragma once
#ifndef  STATE_H
#define STATE_H
#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<stack>
#include<map>
#include<vector>

#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Network.hpp"

class State
{
private:
	sf :: RenderWindow* window;
	std::vector<sf::Texture> texture;
	bool quit;
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit() = 0;
	virtual void endState() = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf:: RenderTarget* target = nullptr) = 0;
};

#endif 