#include "snake_body.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "snake_object.h"
#include "Shader.h"


struct DirChangePoint
{
	glm::vec2 Pos;
	MoveDir Dir;
};

std::vector<DirChangePoint> ListDirChangePoint;

SnakeObject::SnakeObject(vec2 startPos, float velocity, vec2 size, Texture2D texHeader, Texture2D texBody)
	:StartPosition(startPos), Velocity(velocity), Size(size), TextureHeader(TextureHeader), TextureBody(texBody)
{
	//创建第一个身体,作为头
	SnakeBody tempBody(startPos, velocity, size, texHeader);
	ListBodys.push_back(tempBody);
}

SnakeObject::~SnakeObject()
{
	//delete Material::Instance();
}

void SnakeObject::Add()
{
	//在尾部添加一个新的
	SnakeBody* tempBody = &ListBodys.back();
	glm::vec2 tempDir = SnakeObject::GetDirVec(tempBody->Direction);
	glm::vec2 tempPos = tempBody->Position - tempDir * Size.x;
	SnakeBody* newBody = new SnakeBody(tempPos, Velocity, Size, TextureBody);
	newBody->Direction = tempBody->Direction;
	ListBodys.push_back(*newBody);

}

void SnakeObject::GetBodys()
{

}

void SnakeObject::Draw(SpriteRenderer& renderer)
{
	for (size_t i = 0; i < ListBodys.size(); i++)
	{
		ListBodys[i].Draw(renderer);
	}
}

float TimeCounter;
void SnakeObject::Move(float dt)
{
	TimeCounter += dt;
	if (TimeCounter < 1) return;

	TimeCounter = 0;
	//往方向移动一步
	for (size_t i = 0; i < ListBodys.size(); i++)
	{
		SnakeBody* tempBody = &ListBodys[i];
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

void SnakeObject::ChangeDir(MoveDir dir)
{
	MoveDir tempCurDir = ListBodys.front().Direction;
	//完全相反的方向不允许操作
	switch (tempCurDir)
	{
	case Up:
		if (dir == MoveDir::Down) return;
		break;
	case Down:
		if (dir == MoveDir::Up) return;
		break;
	case Left:
		if (dir == MoveDir::Right) return;
		break;
	case Right:
		if (dir == MoveDir::Left) return;
		break;
	}

	DirChangePoint tempDCP;
	tempDCP.Dir = dir;
	tempDCP.Pos = ListBodys.front().Position;
	ListDirChangePoint.push_back(tempDCP);
}

glm::vec2 SnakeObject::GetDirVec(MoveDir dir)
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


