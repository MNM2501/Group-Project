#pragma once
#include "EnemyGameObject.h"
#include "Factory.h"
class Tank :
	public EnemyGameObject
{
public:
	Tank(glm::vec3& entityPos, GLuint entityTextures[3], GLint entityNumElements, int ap, PlayerGameObject* player);

	virtual void render(Shader& shader) override;
	virtual void update(double deltaTime) override;
	
private:
	
	GLuint turretTexture;
	GLuint bulletTexture;
	float angle;

	void fire();

	//handle firing
	float prevTime;
	float cooldown;


};

