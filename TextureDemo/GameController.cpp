#include "GameController.h"
#include "World.h"


//init
string GameController::currentState = HOME;

bool GameController::running = true;
bool GameController::won = false;
std::vector<string> GameController::stateList = { HOME, LEVEL_1, END_LEVEL, SHOP, LEVEL_2, END_LEVEL, SHOP, LEVEL_3, END_LEVEL, END_GAME };

int GameController::currentStateIndex = 0;


//PLAYER STATS
bool GameController::canFireGravityBullet = false;
bool GameController::canDropBombs = false;
bool GameController::firingRateDoubled = false;
bool GameController::immunePlayer = false;
float GameController::firingCooldown = 1.2f;
int GameController::souls = 0;


GameController::GameController()
{}

void GameController::updateState()
{
	if (currentState == LEVEL_1 || currentState == LEVEL_2 || currentState == LEVEL_3)
	{
		if (won)
		{
			//currentState != LEVEL_3 ? currentStateIndex += 3 : currentStateIndex +=2;
			currentStateIndex += 2;
			currentState = stateList[currentStateIndex];
		}
		else
		{
			currentStateIndex ++;
			currentState = stateList[currentStateIndex];
		}
	}

	else if (currentState == END_LEVEL)
	{
		currentStateIndex--;
		currentState = stateList[currentStateIndex];
	}

	else if (currentState == SHOP || currentState == HOME)
	{
		currentStateIndex++;
		currentState = stateList[currentStateIndex];
	}

	else if (currentState == END_GAME)
	{
		currentStateIndex = 1;
		currentState = stateList[currentStateIndex];
	}

	running = true;
	won = false;
}


