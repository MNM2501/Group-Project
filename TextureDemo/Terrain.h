#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"

class Terrain
{

public:
	Terrain(int _rowSize, int _colSize, int** entityGrid, std::vector<GLuint> entityTextures, GLint entityNumElements);

	//render
	void render(Shader&);

private:
	int** grid;
	int rowSize;
	int colSize;
	std::vector<GLuint> textures;
	GLint numElements;


};

