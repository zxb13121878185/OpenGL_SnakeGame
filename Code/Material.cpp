#include "Material.h"
#include <iostream>
#include <sstream>
#include <fstream>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

void Material::LoadShader(std::string name, const char* vsFile, const char* fsFile, const char* gsFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// open files
		std::ifstream vertexShaderFile(vsFile);
		std::ifstream fragmentShaderFile(fsFile);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (gsFile != nullptr)
		{
			std::ifstream geometryShaderFile(gsFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();
	// 2. now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gsFile != nullptr ? gShaderCode : nullptr);
	MapShaders[name] = shader;	//添加到字典中
}

Material* Material::_instance = nullptr;//一定要先初始化为空，否则会编译报错,头文件只是声明，不是定义
Material* Material::Instance()
{
	if (NULL == _instance)
		_instance = new Material();
	return _instance;
}

Material::~Material()
{
	//不能在析构函数中调用释放单例变量，会无限循环调用析构函数
	//不过本身这个代码也不会被调用
	std::cout << "delete Material" << std::endl;
}
