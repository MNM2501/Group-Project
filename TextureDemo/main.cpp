#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //
#include <SOIL/SOIL.h> // read image file
#include <chrono>
#include <thread>

#include "Shader.h"
#include "Window.h"
#include "PlayerGameObject.h"
#include "UIElement.h"
#include "World.h"


// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Group Project";
const unsigned int window_width_g = 1600;
const unsigned int window_height_g = 1200;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 1);

//Global player object
PlayerGameObject* player;

// Global texture info
GLuint tex[7];

// Global game object info
std::vector<GameObject*> gameObjects;

//global background Object
UIElement* background;
UIElement* mmBackground;

//Terrain Object
World* world;

//tiles
std::vector<GLuint> tileTextures;


// Create the geometry for a square (with two triangles)
// Return the number of array elements that form the square
int CreateSquare(void) {
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[]  = {
		//  square (two triangles)
		   //  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
	return sizeof(face) / sizeof(GLuint);
}


void setthisTexture(GLuint w, char *fname)
{
	glBindTexture(GL_TEXTURE_2D, w);

	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setallTexture(void)
{
//	tex = new GLuint[4];
	glGenTextures(7, tex);
	setthisTexture(tex[0], "Ship.png");
	setthisTexture(tex[1], "backgroundScaled.png");
	setthisTexture(tex[2], "grassTile.png");
	setthisTexture(tex[3], "dirtTile.png");
	setthisTexture(tex[4], "mmBackground.png");
	setthisTexture(tex[5], "playbutton.png");
	setthisTexture(tex[6], "playbutton2.png");

	glBindTexture(GL_TEXTURE_2D, tex[0]);
}

void setup(void)
{

	// Set up z-buffer for rendering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	int size = 6;


	// Set up the textures
	setallTexture();

	// Setup the player object (position, texture, vertex count)
	// Note, player object should always be the first object in the game object vector 
	player = new PlayerGameObject(glm::vec3(1.0f, 1.0f, 0.0f), tex[0], size);
	gameObjects.push_back(player);

	// Setup background
	background = new UIElement(glm::vec3(0, 0, 2), tex[1], size);
	background->setScale(glm::vec3(8, 8, 1));

	// Setup MainMenu background
	mmBackground = new UIElement(glm::vec3(0, 0, 1), tex[4], size);
	mmBackground->setScale(glm::vec3(8, 8, 1));
	

	//setup tile textures
	tileTextures.push_back(tex[0]);
	tileTextures.push_back(tex[2]);
	tileTextures.push_back(tex[3]);

	//setup terrain
	int info[12][30] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,2,2,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,1,1,0,0,1,1,1},
	{0,0,0,0,2,2,0,0,0,1,1,1,1,1,1,0,0,2,2,2,2,0,0,2,2,1,1,2,2,2},
	{1,1,1,1,2,2,1,1,1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	int** grid;
	grid = new int*[12];

	for (int i = 0; i < 12; ++i) {
		grid[i] = new int[30];
	}

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			grid[i][j] = info[i][j];
		}
	}
	
	//Setup our world
	world = new World(12, 30, grid, tileTextures, size);
	world->setBoundaries(-1, 30, 6, -10);

}

void controls(void)
{
	GameObject *player = gameObjects[0];
	glm::vec3 curpos = player->getPosition();

	bool buttonPressed = (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) ||
		(glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) ||
		(glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) ||
		(glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS);
	

	// Checking for player input and making changes accordingly
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		player->setVelocity(glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		player->setVelocity(glm::vec3(0, -1, 0));

	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		player->setVelocity(glm::vec3(1, 0, 0));

	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		player->setVelocity(glm::vec3(-1, 0, 0));

	}
	if(!buttonPressed)
	{
		player->setVelocity(glm::vec3(0, 0, 0));
	}
}


//handles main menu
void mainmenu(Window &window, Shader &shader) {
	bool clicked = false;
	while (clicked == false) {
		window.clear(viewport_background_color_g);

		double xpos, ypos;
		glfwGetCursorPos(Window::getWindow(), &xpos, &ypos);


		UIElement* startButton = new UIElement(glm::vec3(-2, 0, 1), tex[5], 6);
		startButton->setScale(glm::vec3(2.0, 1.5, 1));
		UIElement* startButton2 = new UIElement(glm::vec3(-2, 0, 1), tex[6], 6);
		startButton2->setScale(glm::vec3(2.0, 1.5, 1));

		if (xpos > 300 && xpos < 500 && ypos > 535 && ypos < 665) {
			startButton2->render(shader);
			if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				std::cout << "YESSS" << std::endl;
				clicked = true;
			}
		}


		startButton->render(shader);
		mmBackground->render(shader);

		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

}


void gameLoop(Window &window, Shader &shader, double deltaTime)
{
	// Clear background
	window.clear(viewport_background_color_g);

	// set view to zoom out, centred by default at 0,0
	float cameraZoom = 0.25f;
	glm::mat4 centerPlayer = glm::translate(glm::mat4(1.0f), glm::vec3(-player->getPosition().x, -player->getPosition().y, 0));
	glm::mat4 viewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(cameraZoom, cameraZoom, cameraZoom)) * centerPlayer;
	shader.setUniformMat4("viewMatrix", viewMatrix);

	// apply user input
	controls();

	//draw terrain
	world->render(shader);

	// Update and render all game objects
	//printf(" size : %d\n", gameObjects.size());
	for (int i = 0; i < gameObjects.size(); i++) {
		//
		//printf(" i  : %d\n", i);
		// Get the current object
		GameObject* currentGameObject = gameObjects[i];

		// Update game objects
		currentGameObject->update(deltaTime);


		// Check for collision between game objects
		for (int j = i + 1; j < gameObjects.size(); j++) {
			GameObject* otherGameObject = gameObjects[j];

			float distance = glm::length(currentGameObject->getPosition() - otherGameObject->getPosition());
			if (distance < 0.1f) {
				// This is where you would perform collision response between objects
			}
		}

		// Render game objects
		currentGameObject->render(shader);
	}

	//render background
	background->render(shader);

	// Update other events like input handling
	glfwPollEvents();

	// Push buffer drawn in the background onto the display
	glfwSwapBuffers(window.getWindow());
}

// Main function that builds and runs the game
int main(void){
	try {

		// Setup window
		Window window(window_width_g, window_height_g, window_title_g);
		Shader shader("shader.vert", "shader.frag");
		shader.enable();

		setup();
		mainmenu(window, shader);


		// Run the main loop
		double lastTime = glfwGetTime();
		while (!glfwWindowShouldClose(window.getWindow())) {
			
			// Calculate delta time
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			gameLoop(window, shader, deltaTime);
		}
	}
	catch (std::exception &e){
		// print exception and sleep so error can be read
		PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	}

	return 0;
}
