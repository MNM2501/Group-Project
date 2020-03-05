#pragma once
#include "GameObject.h"
class EnemyGameObject :
	public GameObject
{
public:
	EnemyGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float theSpeed, int theHealth,int ap);

	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	virtual void render(Shader& shader) override;
	void decreaseHealth();

	//setters
	void setSpeed(float newSpeed) { speed = newSpeed; }
	void setDead(bool flatline) { dead = flatline; }
	void setAttack(int a) { attackPow = a; }
	void resetRecharge(int r) { recharge = maxRecharge; }
	void decreaseRecharge() { recharge -= 1; }

	//getters
	float getSpeed() { return speed; }
	float getHitBox() { return hitBox; }
	bool isDead() { return dead; }
	int getAttackPow() { return attackPow; }
	int getHealth() { return health; }
	int getRecharge() { return recharge; }



private:
	int attackPow;//attack power
	int health;//hit points
	int recharge;//time until it can fire another shot
	int maxRecharge;//the max value for recharge
	float hitBox;//radius of hitbox
	bool dead;
};

