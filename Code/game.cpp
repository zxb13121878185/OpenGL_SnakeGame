#include "game.h"
#include <sstream>
#include <iostream>

#include <irrklang/irrKlang.h>
using namespace irrklang;

#include "resource_manager.h"
#include "sprite_renderer.h"

using namespace glm;

SpriteRenderer* Renderer;


Game::Game(unsigned int width, unsigned int height)
	:Width(width), Height(height)
{
}

Game::~Game()
{
}

void Game::Init()
{
	ResourceManager::Instance()->LoadShader("shader/sprite.vs", "shader/sprite.fs", nullptr, "sprite");
	mat4 projection = ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::Instance()->GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::Instance()->GetShader("sprite").Use().SetMatrix4("projection", projection);

	ResourceManager::Instance()->LoadTexture("resources/textures/background.jpg", false, "background");
	ResourceManager::Instance()->LoadTexture("resources/textures/awesomeface.png", true, "snakeHeader");
	ResourceManager::Instance()->LoadTexture("resources/textures/block.png", false, "snakeBody");

	Renderer = new SpriteRenderer(ResourceManager::Instance()->GetShader("sprite"));

}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	Renderer->DrawSprite(ResourceManager::Instance()->GetTexture("background"), vec2(0), vec2(this->Width, this->Height), 0);
}

void Game::DoCollisions()
{
}
