#include "RenderCtr.h"

RenderCtr::RenderCtr()
{
}

RenderCtr::~RenderCtr()
{
}

void RenderCtr::DrawSprite(SpriteBaseObject spriteObject)
{

}

void RenderCtr::Init()
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
}

RenderCtr* RenderCtr::_instance = nullptr;
RenderCtr* RenderCtr::Instance()
{
	if (nullptr == _instance)
		_instance = new RenderCtr();

	return _instance;
}
