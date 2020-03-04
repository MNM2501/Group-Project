#include "GameObject.h"

/*
	GameObject is responsible for handling the rendering and updating of objects in the game world
	The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
*/

GameObject::GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) {
	position = entityPosition;
	texture = entityTexture;
	numElements = entityNumElements;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f); // starts out stationary
	xDirection = 1;
	yDirection = 1;
	size = 1;
}

// Updates the GameObject's state
void GameObject::update(double deltaTime) {


	//move player
	glm::vec3 offset = glm::vec3(size / 2 * xDirection, size / 2 * yDirection, 0);
	glm::vec3 futurePos = position + velocity * (float)deltaTime * speed + offset;

	//determine axis we're moving on [part of hotfix for collision bug]
	int axis;
	glm::abs(glm::sign(velocity.x)) > 0 ? axis = 0 : axis = 1;


	if (!World::checkForCollision(futurePos, offset, axis) && !World::boundaryDetection(futurePos))
	{
		//printf("we move.... \n\n\n");
		// Update object position with Euler integration
		position += velocity * (float)deltaTime * speed;

		//update our direction
		if (velocity.x != 0) xDirection = glm::sign(velocity.x);
		if (velocity.y != 0) yDirection = glm::sign(velocity.y);
	}
}

// Renders the GameObject using the shader
void GameObject::render(Shader &shader) {

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1 * xDirection, 1, 1));


	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}


