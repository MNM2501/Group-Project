#include "PlayerGameObject.h"
#include "GameController.h"

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
	hitBox = 0.4;
	damage = 10;
	soulDrop = 0;

	//player firing
	fireCooldown = GameController::firingCooldown;
	startFireCooldown = fireCooldown;
	prevFire = 0.0f;
	canFire = false;

	//player damage
	dmgCooldown = 1.5f;
	prevDmg = 0.0f;
	canReceiveDmg = true;

	//Powerup
	hasPowerup = false;
	startTimePowerup = 0;
	powerupDuration = 0;

	futurePos = glm::vec3();

}


void PlayerGameObject::fire()
{
	prevFire = glfwGetTime();
	canFire = false;
}


void PlayerGameObject::collide(int otherType, glm::vec3 normal, GameObject* otherGameObject)
{
	if (otherType == TERRAIN || otherType == LAVA)
	{
		if (otherType == LAVA)
		{
			receiveDmg(50);
		}
		sv.position += -sv.velocity * sv.deltaTime * speed * 1.1f;

		
		return;
	}

	glm::vec3 p = glm::dot(getVelocity(), normal) * normal;
	glm::vec3 res2 = (float)(-3) * p;
	addForce(p);
}

void PlayerGameObject::receiveDmg(int dmg)
{
	if (GameController::immunePlayer) return;
	GameObject::receiveDmg(dmg);
}

void PlayerGameObject::render(Shader& shader)
{
	shader.setUniform1f("isPlayer", 1.0f);
	GameController::immunePlayer ? shader.setUniform1f("immune", 1.0f) : shader.setUniform1f("immune", -1.0f);
	GameObject::render(shader);
	shader.setUniform1f("isPlayer", -1.0f);
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
	//handle powerup timer
	if (hasPowerup == true && startTimePowerup + powerupDuration < glfwGetTime())
	{
		hasPowerup = false;
		fireCooldown = startFireCooldown;
	}


	// special player updates go here
	sv.position += sv.velocity * (float)deltaTime * speed;
	futurePos = sv.position + sv.velocity; // velocity is normalized so this is one unit away from the player along the velocity vector

	//update our direction
	if (sv.velocity.x != 0) xDirection = glm::sign(sv.velocity.x);
}

void PlayerGameObject::setPowerup(Powerup* p)
{
	if (hasPowerup) return;

	hasPowerup = true;
	startTimePowerup = glfwGetTime();
	powerupDuration = p->duration;
	fireCooldown /= p->cooldownDivider;

}
