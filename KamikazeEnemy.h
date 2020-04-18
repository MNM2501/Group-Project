#pragma once
#include "EnemyGameObject.h"

#define CHASE "chase"
#define PURSUE "pursue"
#define IDLE "idle"

class KamikazeEnemy :
	public EnemyGameObject
{
public:
	KamikazeEnemy(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, PlayerGameObject* player);

	virtual void update(double deltaTime) override;
	virtual void collide(int otherType, glm::vec3 normal, GameObject* otherObject) override;
	virtual void receiveDmg(int dmg) override;
private:
	string state;
};



