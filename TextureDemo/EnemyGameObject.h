#pragma once
#include "GameObject.h"
#include "PlayerGameObject.h"

class EnemyGameObject :
	public GameObject
{
public:
	EnemyGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float theSpeed, int theHealth,int ap,
		PlayerGameObject* player);

	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	virtual void render(Shader& shader) override;
	virtual void collide(string otherType, glm::vec3 normal, GameObject* otherObject) override;

	//setters
	void setSpeed(float newSpeed) { speed = newSpeed; }
	void setAttack(int a) { attackPow = a; }

	//getters
	int getAttackPow() { return attackPow; }



protected:
	int attackPow;//attack power
	float cooldown;//time until it can fire another shot
	float prevTime;

	PlayerGameObject* player;
};

