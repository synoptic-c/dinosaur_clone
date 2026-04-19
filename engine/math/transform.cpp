#include"transform.hpp"
void transform::Translate(glm::mat4& model, const glm::vec2& translation)
{
	model = glm::translate(model, glm::vec3(translation, 0.0f));
}
void transform::RotateYAxis(glm::mat4& model, float angle)
{
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
}
void transform::RotateZAxis(glm::mat4& model, float angle)
{
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}
void transform::Scale(glm::mat4& model, const glm::vec2& scale)
{
	model = glm::scale(model, glm::vec3(scale, 1.0f));
}
void transform::Ortho(glm::mat4& projection, float width, float height)
{
	projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
}
void transform::SetUniformMatrix(unsigned int program, const char* uniformName, const glm::mat4& matrix)
{
	unsigned int matrixUniformLocation = glGetUniformLocation(program, uniformName);
	glUniformMatrix4fv(matrixUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}