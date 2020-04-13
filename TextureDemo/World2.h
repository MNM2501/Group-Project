#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "GameObject.h"



class Tile 
{
	friend class World;

public:
	Tile();
	Tile(int value);

private:
	void updateColor();
	int value;
	glm::vec4 color;
};

class Cell
{
	friend class World;

public:
	Cell();
	
private:
	glm::vec2 gridPos;
	glm::vec3 worldPos;
	Tile tile;
	std::vector<GameObject*> objects;
};

class World
{

public:
	World(GLuint entityTextures, GLint entityNumElements);

	//render
	void render(Shader&);

	//updates objects in grid
	void updateObjects();

	void checkForCollision();

	//clears all the objects in the grid
	void clear();

	//check if objects should be destroyed
	void destroy();



private:
	GLuint texture;
	GLint numElements;
	int horizon;
	int rowSize;
	int colSize;
	Cell* grid[20][20];

	bool outOfBounds(int i, int j);

	bool worldToGridPos(glm::vec3 worldPos, int& i, int&j);
	void gridToWorldPos(int i, int j, glm::vec3* worldPos);

	void explodeBullet(glm::vec3 pos,  float radius);
};

