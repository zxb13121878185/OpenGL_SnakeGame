#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <map>
#include "Shader.h"
#include "sprite_renderer.h"
using namespace glm;

enum MoveDir
{
	Up,
	Down,
	Left,
	Right,
};
class SnakesBody
{
public:
	SnakesBody(glm::vec2 pos, float velocity, glm::vec2 size, unsigned int tex1, unsigned int tex2 = 0);
	~SnakesBody();
	void Draw(Shader* ourShader, unsigned int VAO);
	void Move();
	void Draw(SpriteRenderer& renderer);
public:
	glm::vec2 Position;
	glm::vec2 Size;
	float SpritMoveVelocity;
	MoveDir Direction;
private:
	unsigned int texrure1, texture2;
};

