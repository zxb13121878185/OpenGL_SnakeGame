
#include "SnakesBody.h"
#include "SnakesObject.h"




SnakesBody::SnakesBody(glm::vec2 pos, float velocity, glm::vec2 size, unsigned int tex1, unsigned int tex2)
	:Position(pos), SpritMoveVelocity(velocity), Size(size), texrure1(tex1), texture2(tex2)
{
	Direction = MoveDir::Right;
}

SnakesBody::~SnakesBody()
{

}

void SnakesBody::Draw(Shader* ourShader, unsigned int VAO)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texrure1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// render container
	ourShader->Use();

	glm::mat4 model = glm::mat4(1.0f);
	//Î»ÖÃ
	model = glm::translate(model, glm::vec3(Position, 0.0f));
	//Ðý×ª
	model = glm::translate(model, glm::vec3(0.5f * Size, 0.0f)); // move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	model = glm::translate(model, glm::vec3(-0.5f * Size, 0.0f)); // move origin back
	//Ëõ·Å
	model = glm::scale(model, glm::vec3(Size, 1.0f)); // last scale

	glUniformMatrix4fv(glGetUniformLocation(ourShader->ID, "model"), 1, false, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void SnakesBody::Move()
{
	glm::vec2 tempDir = SnakesObject::GetDirVec(Direction);
	Position += tempDir * Size.x;
}

void SnakesBody::Draw(SpriteRenderer& renderer)
{

}

