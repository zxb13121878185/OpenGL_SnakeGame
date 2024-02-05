#include "game_object.h"

GameObject::GameObject()
	:Position(0, 0), Size(1.0f, 1.0f), Velocity(0), Color(1.0f), Rotation(0), Sprite(), isSolid(false), Destroyed(false)
{

}

GameObject::GameObject(vec2 pos, vec2 size, Texture2D sprite, vec3 color, vec2 velocity)
	:Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0), Sprite(sprite), isSolid(false), Destroyed(false)
{
}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

