#include "SpriteBaseObject.h"

SpriteBaseObject::SpriteBaseObject(Shader* shader, unsigned int tex1, unsigned, int tex2)
	:MyShader(shader),texture1(tex1),texture2(tex2)
{

}

SpriteBaseObject::~SpriteBaseObject()
{
	if (nullptr != MyShader)
	{
		delete MyShader;
	}
}
