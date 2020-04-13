#include "PlayerGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements)
	: GameObject(entityPos, entityTexture, entityNumElements) {

	//info
	type = PLAYER;
	team = ALLIES;
	speed = 3;
	health = 100;
	hitBox = 0.5;

	//player firing
	fireCooldown = 0.2f;
	prevFire = 0.0f;
	canFire = false;

	//player damage
	dmgCooldown = 1.5f;
	prevDmg = 0.0f;
	canReceiveDmg = true;

}


void PlayerGameObject::fire()
{
	prevFire = glfwGetTime();
	canFire = false;
}

void PlayerGameObject::collide(string otherType, glm::vec3 normal, GameObject* otherGameObject)
{

	if (otherType == TERRAIN)
	{
		sv.position += -sv.velocity * sv.deltaTime * speed * 1.1f;
		receiveDmg(0);
		return;
	}

	glm::vec3 p = glm::dot(getVelocity(), normal) * normal;
	glm::vec3 res2 = (float)(-3) * p;
	addForce(p);
}

void PlayerGameObject::receiveDmg(int dmg)
{
	GameObject::receiveDmg(dmg);
}

// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {

	//handles firing timer
	if (prevFire + fireCooldown < glfwGetTime())
	{
		canFire = true;
	}
	//handle dmg timer
	if (prevDmg + dmgCooldown < glfwGetTime())
	{
		canReceiveDmg = true;
	}


	// special player updates go here
	sv.position += sv.velocity * (float)deltaTime * speed;

	//update our direction
	if (sv.velocity.x != 0) xDirection = glm::sign(sv.velocity.x);
}
