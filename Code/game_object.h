#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

using namespace glm;

class GameObject
{
public:
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool isSolid;
	bool Destroyed;
	Texture2D Sprite;
	GameObject();
	GameObject(vec2 pos, vec2 size, Texture2D sprite, vec3 color = vec3(1.0f), vec2 velocity = vec2(0));
	virtual void Draw(SpriteRenderer& renderer);
};

#endif