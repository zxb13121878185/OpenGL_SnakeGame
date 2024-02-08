
#include "snake_body.h"
#include "snake_object.h"

using namespace std;


SnakeBody::SnakeBody(vec2 pos, float velocity, vec2 size, Texture2D tex)
	:Position(pos), Velocity(velocity), Size(size), Texture(tex), Rotation(0), Color(1.0f)
{
	Direction = MoveDir::Right;
}

SnakeBody::~SnakeBody()
{

}

void SnakeBody::Move()
{
	glm::vec2 tempDir = SnakeObject::GetDirVec(Direction);
	Position += tempDir * Size.x;
}

void SnakeBody::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Texture, Position, Size, Rotation, Color);
}

