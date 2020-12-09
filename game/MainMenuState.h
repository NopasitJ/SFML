#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include"State.h"
class MainMenuState :
	public State
{
private:
	//variable
	sf::RectangleShape background;
	//functions
	void initKeyblinds();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int >* supportedKeys);
	virtual ~MainMenuState();

	//Functions

	void endState();

	void updateInput(const  float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);

};
#endif
