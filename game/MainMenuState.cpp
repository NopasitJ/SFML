#include "MainMenuState.h"
void MainMenuState::initKeyblinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybind[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
 }
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int >* supportedKeys)
	:State(window, supportedKeys)
{
	this->initKeyblinds();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}
MainMenuState :: ~MainMenuState()
{


}
void MainMenuState::endState() {

}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
	//updatePlayerinput
}
void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
}