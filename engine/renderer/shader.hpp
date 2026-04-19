#pragma once
#include"../tool/resource_manager.hpp"
#include<glad/glad.h>
#include<iostream>
#include<string>
struct ShaderSource
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};
class Shader
{
private:
	unsigned int m_program;
public:
	void LoadFromFile(const ShaderSource& shaderSource);
	void CreateShader(unsigned int& shader, unsigned int type, std::string& shaderSource);
	void Bind();
	void UnBind();
	unsigned int GetProgram();
	void Destroy();
};