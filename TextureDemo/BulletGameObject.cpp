#include "BulletGameObject.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

const double PI = 3.14159265358979323846;

BulletGameObject::BulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction)
	: GameObject(entityPos, entityTexture, entityNumElements) {
	type = BULLET;
	speed = 5;
	hitBox = 0.3;
	angle = 0;

	sv.velocity = direction;
}


//update function for moving bullet around
void BulletGameObject::update(double deltaTime) {
	// special player updates go here
	sv.position += sv.velocity * (float)deltaTime * speed;

	//determine angle
	glm::vec3 direction = glm::normalize(sv.velocity);
	angle = acos(glm::dot(direction, glm::vec3(1.0f, 0.0f, 0.0f)));
	//cout << angle << endl;

	//update our direction
	if (sv.velocity.x != 0) xDirection = glm::sign(sv.velocity.x);
}

//collision for this object
void BulletGameObject::collide(string otherType, glm::vec3 normal, GameObject* otherObject)
{
	if(otherObject != NULL)
		otherObject->receiveDmg(10);

	shouldDie = true;
}

void BulletGameObject::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), sv.position);
	float angleDeg = (180 / PI) * angle;
	glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), angleDeg, glm::vec3(0, 0, 1.0));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.5, 0.5));

	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix*rotateMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
