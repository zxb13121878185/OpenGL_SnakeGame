#pragma once

#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game
{
public:
	bool Keys[1024];
	bool KeysProcessed[1024];
	unsigned int Width, Height;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void ProcessInput(float dt);
	void GetKeyPress(int key);
	void GetKeyRelease(int key);
	void Update(float dt);
	void Render();
	void DoCollisions();
};


#endif