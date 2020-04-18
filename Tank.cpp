#include "Tank.h"



Tank::Tank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player) :
	EnemyGameObject(entityPos, entityTextures, entityNumElements, 1.0f, 20, 10, player), turretTexture(entityTextures[2])
{
	type = TANK;
	team = ENEMIES;
	xDirection = 1;
	angle = 0.0f;
	soulDrop = 20;

	//firing
	prevTime = 0.0f;
	cooldown = 1.0f;
}

void Tank::fire()
{
	if (glm::distance(player->getPosition(), getPosition()) > 8) return;
	Factory::spawnBulletGameObject(getPosition() + glm::vec3(0, 0.0f, 0), bulletTexture,
		glm::normalize(player->getPosition() - getPosition()), this->team, 10);

	prevTime = glfwGetTime();
}

void Tank::update(double deltaTime)
{
	//point turret towards player
	glm::vec3 direction = glm::normalize(player->getPosition() - getPosition());
	angle = acos(glm::dot(direction, glm::vec3(1.0f, 0.0f, 0.0f)));

	//handles firing timer
	if (prevTime + cooldown < glfwGetTime())
	{
		fire();
	}

	GameObject::update(deltaTime);
}


void Tank::render(Shader& shader)
{
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//handles hurt effect
	if (!canReceiveDmg)
	{
		if (shaderClockSet == false)
		{
			shader.setUniform1f("startTime", glfwGetTime());
			shaderClockSet = true;
		}

		shader.setUniform1f("hurt", 1.0f);
	}
	else
	{
		shader.setUniform1f("hurt", -1.0f);
	}

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), sv.position + glm::vec3(0.0f, -0.25f, 0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5 * xDirection, 0.5, 0));


	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;
	glm::mat4 parentTransform = transformationMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);


	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);


	//draw turret-----------------------------------------------------------------------------------

	// Bind the entities texture
	double PI = 3.14159265358979323846;
	glBindTexture(GL_TEXTURE_2D, turretTexture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	float newAngle = (180 / PI) * angle;
	glm::mat4 translationMatrixTurret = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.25f, 0.0f));
	glm::mat4 scaleMatrixTurret = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.4f, 1.0f));
	glm::mat4 rotationMatrixTurret = glm::rotate(glm::mat4(1.0f), newAngle, glm::vec3(0, 0, 1));
	glm::mat4 offset = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0, 0));
	glm::mat4 offsetUndo = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0, 0));

	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 localTransform = translationMatrixTurret * scaleMatrix * offsetUndo * rotationMatrixTurret * offset;
	transformationMatrix = parentTransform * localTransform;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	shader.setUniform1f("hurt", -1.0f);

}


