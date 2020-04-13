#pragma once
#include "UIElement.h"
#include <vector>
#include "PlayerGameObject.h"

class HealthBar :
	public UIElement
{
public:
	HealthBar(glm::vec3 &entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, PlayerGameObject* player);
	void updateHealthTexture();
	void render(Shader& shader) override;

private:
	std::vector<GLuint> textures;
	PlayerGameObject* player;
	
	int health;

};

