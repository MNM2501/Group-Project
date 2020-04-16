#include "Store.h"
#include "GameController.h"

Store::Store(GLuint entityTexture, GLint entityNumElements, Product* p1, Product* p2, Product* p3){
	texture = entityTexture;
	numElements = entityNumElements;
	products[0] = p1;
	products[1] = p2;
	products[2] = p3;

	products[0]->setSoldOut(GameController::firingRateDoubled);
	products[1]->setSoldOut(GameController::canFireGravityBullet);
	products[2]->setSoldOut(GameController::canDropBombs);

}

bool Store::isNotSoldout(int p) {
	if (products[p - 1]->getSoldOut()) {
		return false;
	}
	else {
		return true;
	}
}

bool Store::buy(int p) {

	GameController::souls -= products[p - 1]->cost;
	cout << "You now have " << GameController::souls << " souls." << endl;

	if (isNotSoldout(p)) {
		products[p - 1]->setSoldOut(true);

		if (p == 1)
		{
			GameController::firingRateDoubled = true;
			GameController::firingCooldown /= 2;
		}

		else if (p == 2)
		{
			GameController::canFireGravityBullet = true;
		}

		else if (p == 3)
		{
			GameController::canDropBombs = true;
		}

		return true;
	}
	else {
		return false;
	}
}

void Store::update()
{
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
		if (isNotSoldout(1) && GameController::souls >= products[0]->cost) {
			buy(1);
		}
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
		if (isNotSoldout(2) && GameController::souls >= products[1]->cost) {
			buy(2);
		}
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
		if (isNotSoldout(3) && GameController::souls >= products[2]->cost) {
			buy(3);
		}
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_L) == GLFW_PRESS) {
		GameController::running = false;
	}
	
}
void Store::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,3.5,0.0));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 3.0, 0.0));
	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix*scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	for (int x = 0; x < 3; x++) {
		products[x]->render(shader);
	}
}