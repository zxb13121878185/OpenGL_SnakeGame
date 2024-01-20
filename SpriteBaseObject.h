#pragma once
#include "Code/Shader.h"
class SpriteBaseObject
{
public:
	SpriteBaseObject(Shader * shader,unsigned int tex1,unsigned,int tex2);
	~SpriteBaseObject();

private:
	Shader* MyShader;
	unsigned int texture1, texture2;
};

