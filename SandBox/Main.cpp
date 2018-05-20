#include "stdafx.h"
#include "vld.h"
#include "Game.h"
#pragma comment(lib,"xinput.lib")

int main(int argc, char* argv[]) {

	Game game;

	//init everything (managers etc)
	game.Initialize();

	//init scenes
	game.LoadGameData();

	//run game
	game.Run();
	
	//clean everything
	game.Cleanup();

	return 0;
}
