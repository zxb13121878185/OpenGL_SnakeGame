#include "SnakesBody.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SnakesObject.h"
#include "Shader.h"

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int texture1;
unsigned int texture2;
glm::mat4 projection;

struct DirChangePoint
{
	glm::vec2 Pos;
	MoveDir Dir;
};

std::vector<DirChangePoint> ListDirChangePoint;

SnakesObject::SnakesObject(glm::vec2 startPos, float velocity, glm::vec2 size)
	:Velocity(velocity)
{
	//创建第一个身体,作为头
	SnakesBody tempBody(startPos, velocity, size, texture2);
	ListBodys.push_back(tempBody);
}

SnakesObject::~SnakesObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//delete Material::Instance();
}

void SnakesObject::Add()
{
	//在尾部添加一个新的
	SnakesBody* tempBody = &ListBodys.back();
	glm::vec2 tempDir = SnakesObject::GetDirVec(tempBody->Direction);
	glm::vec2 tempPos = tempBody->Position - tempDir * tempBody->Size.x;
	SnakesBody* newBody = new SnakesBody(tempPos, Velocity, tempBody->Size, texture1);
	ListBodys.push_back(*newBody);

}

void SnakesObject::GetBodys()
{

}

void SnakesObject::Draw()
{

}

float TimeCounter;
void SnakesObject::Move(float dt)
{
	TimeCounter += dt;
	if (TimeCounter < 1) return;

	TimeCounter = 0;
	//往方向移动一步
	for (size_t i = 0; i < ListBodys.size(); i++)
	{
		SnakesBody* tempBody = &ListBodys[i];
		for (int j = 0; j < ListDirChangePoint.size(); j++)
		{
			DirChangePoint* tempPoint = &ListDirChangePoint[j];
			//到达拐点就按拐点的方向移动
			if (tempPoint->Pos == tempBody->Position)
			{
				//改变它的方向
				tempBody->Direction = tempPoint->Dir;
				//如果已经是最后一个了就删掉这个拐点
				if (i == ListBodys.size() - 1)
				{
					ListDirChangePoint.erase(ListDirChangePoint.begin() + j);
					//std::cout << "delete change point" + ListDirChangePoint.size() << std::endl;
				}
			}
		}
		tempBody->Move();
	}
}

void SnakesObject::ChangeDir(MoveDir dir)
{
	DirChangePoint tempDCP;
	tempDCP.Dir = dir;
	tempDCP.Pos = ListBodys.front().Position;
	ListDirChangePoint.push_back(tempDCP);
}

glm::vec2 SnakesObject::GetDirVec(MoveDir dir)
{
	glm::vec2 tempDir = glm::vec2(0);

	switch (dir)
	{
	case Up:
		tempDir.x = 0;
		tempDir.y = -1;
		break;
	case Down:
		tempDir.x = 0;
		tempDir.y = 1;
		break;
	case Left:
		tempDir.x = -1;
		tempDir.y = 0;
		break;
	case Right:
		tempDir.x = 1;
		tempDir.y = 0;
		break;
	default:
		break;
	}
	return tempDir;
}


