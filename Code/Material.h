#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Shader.h"



class Material
{
public:
	std::map<std::string, Shader> MapShaders;
	void LoadShader(std::string name, const char* vsFile, const char* fsFile, const char* gsFile = nullptr);

public:
	static Material* Instance();
	~Material();

private:
	static Material* _instance;
	Material() {}
};

