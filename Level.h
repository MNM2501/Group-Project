#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include "UIElement.h"

using namespace std;

class Level
{
	friend class World;

public:
	Level(string fileName, std::vector<GLuint> entityTextures, glm::vec3 playerStart, UIElement* background);

private:
	UIElement* background;
	glm::vec3 playerStart;
	std::vector<GLuint> textures;
	int xHorizon;
	int yHorizon;
	int id;
	int rowSize;
	int colSize;
	std::vector<std::vector<int>> terrain;
};

