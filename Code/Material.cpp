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
	MapShaders[name] = shader;	//��ӵ��ֵ���
}

Material* Material::_instance = nullptr;//һ��Ҫ�ȳ�ʼ��Ϊ�գ��������뱨��,ͷ�ļ�ֻ�����������Ƕ���
Material* Material::Instance()
{
	if (NULL == _instance)
		_instance = new Material();
	return _instance;
}

Material::~Material()
{
	//���������������е����ͷŵ���������������ѭ��������������
	//���������������Ҳ���ᱻ����
	std::cout << "delete Material" << std::endl;
}
