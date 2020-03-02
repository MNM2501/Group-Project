#include "BulletGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

BulletGameObject::BulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,float theSpeed,float theAngle)
	: GameObject(entityPos, entityTexture, entityNumElements) {
	speed = theSpeed;
	angle = theAngle;
}

// Update function for moving the player object around
void BulletGameObject::update(double deltaTime) {

	// special player updates go here

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::update(deltaTime);
}
void BulletGameObject::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1.0));

	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix*rotateMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
