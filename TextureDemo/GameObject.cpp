#include "GameObject.h"

/*
	GameObject is responsible for handling the rendering and updating of objects in the game world
	The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
*/

GameObject::GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) {
	//info
	type = OBJECT;
	sv.position = entityPosition;
	sv.minv = 1;
	sv.maxSpeed = 1.0f;
	texture = entityTexture;
	numElements = entityNumElements;
	xDirection = 1;
	yDirection = 1;
	hitBox = 0.5;
	shouldDie = false;
	team = "";
	sv.noGravity = true;
	soulDrop = 0;

	//health
	health = 20;
	dmgCooldown = 2.0f;
	prevDmg = 0.0f;
	canReceiveDmg = true;
	shaderClockSet = false;
}

void GameObject::addForce(glm::vec3 force)
{
	sv.update(force);
}

void GameObject::stop()
{
	sv.momentum = glm::vec3(0);
}

// Updates the GameObject's state
void GameObject::update(double deltaTime) {

	//update delta time in state vector
	sv.deltaTime = deltaTime;

	//update our direction
	if (sv.velocity.x != 0) xDirection = glm::sign(sv.velocity.x);

	//handle  receiving dmg timer
	if (prevDmg + dmgCooldown < glfwGetTime())
	{
		canReceiveDmg = true;
	}
}

//handle collision
void GameObject::collide(int otherType, glm::vec3 normal, GameObject* otherObject)
{
	//--
}

void GameObject::receiveDmg(int dmg)
{
	if (type == LAVA) return; // stops lava from receiving damge (hotfix)
	if (!canReceiveDmg) return;
	canReceiveDmg = false;
	shaderClockSet = false;

	prevDmg = glfwGetTime();
	health - dmg  < 0 ? health = 0 : health -= dmg;

	if (health <= 0)
		shouldDie = true;
}

// Renders the GameObject using the shader
void GameObject::render(Shader &shader) {

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	
	//handles hurt effect
	if (!canReceiveDmg)
	{
		if (shaderClockSet == false)
		{
			shader.setUniform1f("startTime", glfwGetTime());
			shaderClockSet = true;
		}

		shader.setUniform1f("hurt", 1.0f);
	}
	else
	{
		shader.setUniform1f("hurt", -1.0f);
	}

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), sv.position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1 * xDirection, 1, 1));


	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	shader.setUniform1f("hurt", -1.0f);

}


