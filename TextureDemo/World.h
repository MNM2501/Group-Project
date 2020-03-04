#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"

class World
{

public:
	World(int _rowSize, int _colSize, int** entityGrid, std::vector<GLuint> entityTextures, GLint entityNumElements);

	//render
	static void render(Shader&);

	//check for collison
	static bool checkForCollision(glm::vec3);

	//boundary detection
	static bool boundaryDetection(glm::vec3);

	//setters 
	static void setBoundaries(int l, int r, int u, int d)
	{
		leftBoundary = l;
		rightBOundary = r;
		upperBoundary = u;
		lowerBoundary = d;
	}

private:
	static int** worldGrid;
	static int rowSize;
	static int colSize;
	static std::vector<GLuint> textures;
	static GLint numElements;

	static int leftBoundary;
	static int rightBOundary;
	static int upperBoundary;
	static int lowerBoundary;

	//convert grid pos to world pos and vise versa
	static glm::vec3 gridToWorldPos(int, int);
	static bool worldToGridPos(glm::vec3, int&, int&);

	
};

