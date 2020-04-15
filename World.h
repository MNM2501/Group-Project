#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "GameObject.h"
#include "Level.h"
#include "ObjectTypes.h"


class Cell
{
	friend class World;

public:
	Cell();

private:

	bool isTerrain;

	GLuint texture;
	glm::vec2 gridPos;
	glm::vec3 worldPos;
	std::vector<GameObject*> objects;
};

class World
{

public:
	World(std::vector<GLuint> entityTextures, GLint entityNumElements);

	//loads a level
	static void loadLevel(Level* level);

	//runs the world
	static void run();

	//render
	static void render(Shader&);

	//All game objects in the world
	static std::vector<GameObject*> gameObjects;


private:
	static std::vector<GLuint> textures;
	static GLint numElements;
	static Level* currentLevel;
	static std::vector<std::vector<Cell*>> grid;

	//convert grid pos to world pos and vise versa
	static void gridToWorldPos(int i, int j, glm::vec3* worldPos);
	static bool worldToGridPos(glm::vec3, int&, int&);

	static bool outOfBounds(int i, int j);

	//check for collison
	static void checkForCollision();

	//check for object to be destroyed
	static void destroy();

	//update object positions in grid
	static void updateObjects();

	//clears our grid - done at the end of every frame
	static void clear();
};

