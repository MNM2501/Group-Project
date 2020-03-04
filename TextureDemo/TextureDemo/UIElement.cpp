#include "UIElement.h"

UIElement::UIElement(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements)
{
	position = entityPos;
	texture = entityTexture;
	numElements = entityNumElements;
}

void UIElement::render(Shader &shader)
{
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glm::mat4 UIMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.25));
	shader.setUniformMat4("viewMatrix", UIMatrix);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);


	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

