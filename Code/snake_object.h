#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "snake_body.h"
using namespace glm;


class SnakeObject
{
public:
	SnakeObject(vec2 startPos, float velocity, vec2 size, Texture2D texHeader, Texture2D texBody);
	~SnakeObject();

	/// <summary>
	/// 在最后一个反方向添加一个身体
	/// </summary>
	/// <param name="body"></param>
	void Add();
	void GetBodys();
	void Draw(SpriteRenderer& renderer);

	void Move(float dt);

	void ChangeDir(MoveDir dir);

public:
	static 	vec2 GetDirVec(MoveDir dir);

	float Velocity;
	vec2 StartPosition, Size;
	Texture2D TextureHeader, TextureBody;

private:
	std::vector <SnakeBody> ListBodys;
};

