#include "EnemyGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

EnemyGameObject::EnemyGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float theSpeed, int theHealth, int ap)
	: GameObject(entityPos, entityTexture, entityNumElements) {
	speed = theSpeed;
	health = theHealth;
	attackPow = ap;
	recharge = 600;
	maxRecharge = 600;
	dead = false;
	hitBox = 0.5;
}

// Update function for moving the player object around
void EnemyGameObject::update(double deltaTime) {
	// Update object position with Euler integration
	position += velocity * (float)deltaTime;
}

void EnemyGameObject::render(Shader& shader) {
	GameObject::render(shader);
}
void EnemyGameObject::decreaseHealth() {
	health -= 1;
	if (health <= 0) {
		setDead(true);
	}
}
