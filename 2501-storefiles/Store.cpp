#include "Store.h"

Store::Store(GLuint entityTexture, GLint entityNumElements, Product* p1, Product* p2, Product* p3){
	texture = entityTexture;
	numElements = entityNumElements;
	products[0] = p1;
	products[1] = p2;
	products[2] = p3;
}

bool Store::isNotSoldout(int p) {
	if (products[p - 1]->getSoldOut()) {
		return false;
	}
	else {
		return true;
	}
}

bool Store::buy(int p) {
	if (isNotSoldout(p)) {
		products[p - 1]->setSoldOut(true);
		return true;
	}
	else {
		return false;
	}
}
void Store::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,3.5,0.0));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 3.0, 0.0));
	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix*scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	for (int x = 0; x < 3; x++) {
		products[x]->render(shader);
	}
}