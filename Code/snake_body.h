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
class SnakeBody
{
public:
	SnakeBody(vec2 pos, float velocity, vec2 size, Texture2D tex);
	~SnakeBody();
	void Move();
	void Draw(SpriteRenderer& renderer);
public:
	vec2 Position, Size;
	float Velocity;
	float Rotation;
	vec3 Color;
	MoveDir Direction;
	Texture2D Texture;
};

