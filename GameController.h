#pragma once
#include <vector>
#include <string>

#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Window.h"
#include "Shader.h"
#include <string>

#define HOME "HOME"
#define SHOP "SHOP"
#define END_LEVEL "EL"
#define END_GAME "EG"
#define LEVEL_1 "L1"
#define LEVEL_2 "L2"
#define LEVEL_3 "L3"

using namespace std;


class GameController
{
public:
	GameController();

	static string currentState;
	static bool running;
	static bool won;

	static void updateState();

	//player stats
	static bool canDropBombs;
	static bool canFireGravityBullet;
	static bool firingRateDoubled;
	static bool immunePlayer;
	static float firingCooldown;
	static int souls;

private:
	
	static vector<string> stateList;
	static int currentStateIndex;
};

