#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"

class Product {
public:
	Product(glm::vec3& entityPosition, GLuint entityTexture, GLuint entityTexture2, GLint entityNumElements, int cost);

	void render(Shader& shader);

	bool getSoldOut() { return soldOut; }

	void setSoldOut(bool value) { soldOut = value; }

	int cost;
protected:
	glm::vec3 position;
	// Object's details
	GLint numElements;
	float objectSize; // Not currently being used (will be needed for collision detection when objects have a different scale)
	bool soldOut;

	// Object's texture
	GLuint texture;
	GLuint textureSoldout;
};
