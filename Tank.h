#pragma once
#include "EnemyGameObject.h"
#include "Factory.h"
class Tank :
	public EnemyGameObject
{
public:
	Tank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player);

	virtual void render(Shader& shader) override;
	virtual void update(double deltaTime) override;
	
private:

	virtual void fire() override;

	GLuint turretTexture;
	float angle;


};

