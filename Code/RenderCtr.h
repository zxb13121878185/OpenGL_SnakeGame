#pragma once
#include "../SpriteBaseObject.h"


class RenderCtr
{
public:
	RenderCtr();
	~RenderCtr();
	void DrawSprite(SpriteBaseObject spriteObject);
	void Init();

public:
	static RenderCtr* Instance();

private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	static RenderCtr* _instance;
};

