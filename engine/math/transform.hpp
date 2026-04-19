#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
namespace transform
{
	void Translate(glm::mat4& model, const glm::vec2& translation);
	void RotateYAxis(glm::mat4& model, float angle);
	void RotateZAxis(glm::mat4& model, float angle);
	void Scale(glm::mat4& model, const glm::vec2& scale);
	void Ortho(glm::mat4& projection, float width, float height);
	void SetUniformMatrix(unsigned int program, const char* uniformName, const glm::mat4& matrix);
}