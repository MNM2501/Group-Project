#include "BulletGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

BulletGameObject::BulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,float theSpeed,float theAngle, int borrowedTime)
	: GameObject(entityPos, entityTexture, entityNumElements) {
	speed = theSpeed;
	angle = theAngle;
	lifeSpan = borrowedTime;
	dead = false;
	hitBox = 0.5;
}


// Update function for moving the player object around
void BulletGameObject::decreaseLifeSpan() {
	lifeSpan -= 1;
	if (lifeSpan <= 0) {
		setDead(true);
	}
}

//update function for moving player around
void BulletGameObject::update(double deltaTime) {
	// Update object position with Euler integration
	position += velocity * (float)deltaTime;
}


void BulletGameObject::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1.0));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.5, 0.5));

	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix*rotateMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
