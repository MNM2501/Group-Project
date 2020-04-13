#include "EnemyGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

EnemyGameObject::EnemyGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float theSpeed, int theHealth, int ap,
	PlayerGameObject * player)
	: GameObject(entityPos, entityTexture, entityNumElements) {
	type = ENEMY;
	speed = theSpeed;
	health = theHealth;
	attackPow = ap;

	//firing timer
	prevTime = 0.0f;
	cooldown = 1.0f;

	this->player = player;
}

void EnemyGameObject::collide(string otherType, glm::vec3 normal, GameObject* otherObject)
{
	if (otherType == PLAYER)
		otherObject->receiveDmg(10);
}

void EnemyGameObject::update(double deltaTime) {

	// special player updates go here
	GameObject::update(deltaTime);
}

void EnemyGameObject::render(Shader& shader) {
	GameObject::render(shader);
}

