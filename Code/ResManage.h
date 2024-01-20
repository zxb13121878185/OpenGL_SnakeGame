#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Shader.h"



class ResManage
{
public:
	std::map<std::string, Shader> MapShaders;
	void LoadShader(std::string name, const char* vsFile, const char* fsFile, const char* gsFile = nullptr);

public:
	static ResManage* Instance();
	~ResManage();

private:
	static ResManage* _instance;
	ResManage() {}
};

