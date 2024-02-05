#pragma once

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"
#include <memory>
#include <mutex>

using namespace std;

class ResourceManager
{
public:
	static shared_ptr<ResourceManager> Instance();

	Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, string name);
	Shader GetShader(string name);
	Texture2D LoadTexture(const char* file, bool alpha, string  name);
	Texture2D GetTexture(string name);
	void Clear();

	~ResourceManager();

public:

	map<string, Shader> Shaders;
	map<string, Texture2D> Textures;

private:
	ResourceManager();

};

#endif