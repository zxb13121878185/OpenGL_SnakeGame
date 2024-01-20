#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "SnakesObject.h"



// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// The Width of the screen
const unsigned int SCREEN_WIDTH = 1920;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 1080;

glm::vec2 BodySize = glm::vec2(50.0f, 50.0f);
glm::vec2 StartPos = glm::vec2(0);
float Velocity = 1.0f;
SnakesObject* snakesObject;

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snakes", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	SnakesObject::DrawInit(SCREEN_WIDTH, SCREEN_HEIGHT);
	snakesObject = new SnakesObject(StartPos, Velocity, BodySize);


	float lastFrame = 0;
	float deltaTime = 0;


	while (!glfwWindowShouldClose(window))
	{
		// calculate delta time
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		snakesObject->Draw();
		snakesObject->Move(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete(snakesObject);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			//std::cout << "Press" << std::endl;
		}
		else if (action == GLFW_RELEASE)
		{
			//std::cout << "Release" << std::endl;
		}
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		snakesObject->Add();
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		snakesObject->ChangeDir(MoveDir::Up);
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		snakesObject->ChangeDir(MoveDir::Down);
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		snakesObject->ChangeDir(MoveDir::Left);
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		snakesObject->ChangeDir(MoveDir::Right);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
