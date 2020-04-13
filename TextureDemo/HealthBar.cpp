#include "HealthBar.h"

HealthBar::HealthBar(glm::vec3 &entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, PlayerGameObject* player) : 
	UIElement(entityPos, entityTextures[0], entityNumElements)
{
	textures = entityTextures;
	health = 100;
	this->player = player;
}

void HealthBar::updateHealthTexture()
{
	health = player->getHealth();
	int index = ceil(health / 10);
	//-- determine texture
	texture = textures[index];
}

void HealthBar::render(Shader& shader)
{
	updateHealthTexture();
	UIElement::render(shader);
}


