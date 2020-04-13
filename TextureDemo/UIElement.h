#pragma once
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"

class UIElement
{
public:
	UIElement(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);

	//renders UIElement
	virtual void render(Shader &shader);

	//Setters
	void setScale(glm::vec3 newScale) { scale = newScale; }
protected:
	// Object's texture
	GLuint texture;
	GLint numElements;

	glm::vec3 position;
	glm::vec3 scale;
};

