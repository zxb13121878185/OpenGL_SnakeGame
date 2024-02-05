#pragma once
#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H


#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"
using namespace glm;

class SnakeObject :GameObject
{

public:
	SnakeObject();
};

#endif // !SNAKEOBJECT_H