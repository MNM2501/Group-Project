#include "Product.h"

Product::Product(glm::vec3& entityPosition, GLuint entityTexture, GLuint entityTexture2, GLint entityNumElements, int cost) {
	position = entityPosition;
	texture = entityTexture;
	textureSoldout = entityTexture2;
	numElements = entityNumElements;
	soldOut = false;
	this->cost = cost;
}

void Product::render(Shader& shader) {
	// Bind the entities texture
	if (soldOut) {
		glBindTexture(GL_TEXTURE_2D, textureSoldout);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(5.0,3.0,0.0));

	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix*scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}