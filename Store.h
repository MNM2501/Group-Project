#pragma once
#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "Product.h"
#include "Window.h"

class Store {
public:
	Store(GLuint entityTexture, GLint entityNumElements, Product* p1, Product* p2, Product* p3);

	void render(Shader& shader);

	void update();

	//returns true if the product in question is not sold out. input 1-3
	bool isNotSoldout(int p);

	//returns true if we were able to buy the requested product. If we were able to buy it set that products soldOut
	//value to true. input 1-3
	bool buy(int p);

protected:
	Product* products[3];
	GLuint texture;
	GLint numElements;
};
