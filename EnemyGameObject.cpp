#include "EnemyGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

EnemyGameObject::EnemyGameObject(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, float theSpeed, int theHealth, int ap,
	PlayerGameObject * player)
	: GameObject(entityPos, entityTextures[0], entityNumElements) 
{
	type = ENEMY;
	team = ENEMIES;
	speed = theSpeed;
	health = theHealth;
	attackPow = ap;
	sv.velocity = glm::vec3(0, 1, 0);

	bulletTexture = entityTextures[1];

	dmgCooldown = 0.2f;

	//firing timer
	prevTime = 0.0f;
	cooldown = 2.0f;

	this->player = player;

	//up and down position
	upYPos = sv.position.y + 1;
	downYPos = sv.position.y - 1;
}

void EnemyGameObject::collide(int otherType, glm::vec3 normal, GameObject* otherObject)
{
	if (otherType == PLAYER)
		otherObject->receiveDmg(10);
}

void EnemyGameObject::fire()
{
	Factory::spawnBulletGameObject(getPosition() + glm::vec3(0, 0.0f, 0), bulletTexture, numElements,
		glm::normalize(glm::vec3(-1,0,0)), this->team, 10);

	prevTime = glfwGetTime();
}

void EnemyGameObject::update(double deltaTime) {

	// special player updates go here
	if (sv.position.y > upYPos || sv.position.y < downYPos)
		sv.velocity *= -1.0f;

	sv.position += sv.velocity * (float)deltaTime * speed;

	//handles firing timer
	if (prevTime + cooldown < glfwGetTime())
	{
		fire();
	}

	GameObject::update(deltaTime);
}

void EnemyGameObject::render(Shader& shader) {
	GameObject::render(shader);
}

