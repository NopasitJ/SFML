#include<SFML/Graphics.hpp>
#include"Game.h"
#include<time.h>
#include"Menu.h"
int main()
{
	Menu menu(window.getSize().x, window.getSize().y);
	window.draw();
	srand(time_t(static_cast<unsigned>(0)));

	Game game;
	game.run();

	return 0;
}