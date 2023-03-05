#include "stdafx.h"
#include "Game.h"

using namespace std;
int main()
{
	Game game;
	
	while (game.getWindow().isOpen())
	{
		
		game.render();
		game.update();
		
		
	}
	
}

