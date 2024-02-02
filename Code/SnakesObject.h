#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "SnakesBody.h"



class SnakesObject
{
public:
	SnakesObject(glm::vec2 startPos, float velocity, glm::vec2 size);
	~SnakesObject();

	/// <summary>
	/// 在最后一个反方向添加一个身体
	/// </summary>
	/// <param name="body"></param>
	void Add();
	void GetBodys();
	void Draw();

	void Move(float dt);

	void ChangeDir(MoveDir dir);

public:
	static 	glm::vec2 GetDirVec(MoveDir dir);

private:
	std::vector <SnakesBody> ListBodys;
	float Velocity;
};

