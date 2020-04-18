#include "KamikazeEnemy.h"



KamikazeEnemy::KamikazeEnemy(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements,	PlayerGameObject* player): 
	EnemyGameObject(entityPos, entityTextures, entityNumElements, 1, 1, 0, player)
{
	type = KAMIKAZE;
	state = IDLE;
}

void KamikazeEnemy::update(double deltaTime)
{
	//determine state
	float distance = glm::distance(player->getPosition(), sv.position);

	if (distance < 3) state = PURSUE;
	if (distance < 6) state = CHASE;
	else state = IDLE;


	if (state == IDLE)
	{
		sv.velocity = glm::vec3(0);
	}

	if (state == CHASE)
	{
		glm::vec3 direction = glm::normalize(player->getPosition() - sv.position);
		sv.velocity = direction;
		sv.position += sv.velocity * speed * (float)deltaTime;
	}

	if (state == PURSUE)
	{
		glm::vec3 playerFuturePos = player->getFuturePos();
		glm::vec3 direction = glm::normalize(playerFuturePos - sv.position);
		sv.velocity = direction;
		sv.position += sv.velocity * speed * (float)deltaTime;
	}

	//update our direction
	if (sv.velocity.x != 0) xDirection = -glm::sign(sv.velocity.x);
}

void KamikazeEnemy::receiveDmg(int dmg)
{
	return;
}

void KamikazeEnemy::collide(int otherType, glm::vec3 normal, GameObject* otherObject)
{
	if (otherType == PLAYER)
	{
		otherObject->receiveDmg(30);
		shouldDie = true;
	}

	if (otherType == TERRAIN)
	{
		shouldDie = true;
	}
}
