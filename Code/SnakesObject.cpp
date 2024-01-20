#include "SnakesBody.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "SnakesObject.h"
#include "Shader.h"
#include "ResManage.h"

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
	Shader* ourShader = &ResManage::Instance()->MapShaders["Snakes"];
	for (size_t i = 0; i < ListBodys.size(); i++)
	{
		ListBodys[i].Draw(ourShader, VAO);
	}
}
void SnakesObject::DrawInit(int screenWidth, int screenHeight)
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
			// ------------------------------------------------------------------
	float vertices[] = {
		// pos      // tex
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	ResManage::Instance()->LoadShader("Snakes", "shader/texture.vs", "shader/texture.fs");
	Shader* ourShader = &ResManage::Instance()->MapShaders["Snakes"];
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->Use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	glUniform1i(glGetUniformLocation(ourShader->ID, "texture1"), 0);
	// or set it via the texture class
	ourShader->SetInteger("texture2", 1);

	// configure shaders
	projection = glm::ortho(0.0f, static_cast<float>(screenWidth),
		static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(ourShader->ID, "projection"), 1, false, glm::value_ptr(projection));
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


