#include"shader.hpp"
void Shader::LoadFromFile(const ShaderSource& shaderSource)
{
	std::string vertexSource;
	resourcemanager::LoadShaderSource(shaderSource.vertexShaderSource.c_str(), vertexSource);
	unsigned int vertexShader;
	CreateShader(vertexShader, GL_VERTEX_SHADER, vertexSource);
	std::string fragmentSource;
	resourcemanager::LoadShaderSource(shaderSource.fragmentShaderSource.c_str(), fragmentSource);
	unsigned int fragmentShader;
	CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentSource);
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	int result;
	glGetProgramiv(m_program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int logLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
		std::string infoLog(logLength, '\0');
		glGetProgramInfoLog(m_program, logLength, NULL, infoLog.data());
		std::cout << infoLog << std::endl;
		glDeleteProgram(m_program);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void Shader::CreateShader(unsigned int& shader, unsigned int type, std::string& shaderSource)
{
	shader = glCreateShader(type);
	const char* source = shaderSource.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::string infoLog(logLength,'\0');
		glGetShaderInfoLog(shader, logLength, NULL, infoLog.data());
		std::cout << infoLog << std::endl;
		glDeleteShader(shader);
	}
}
void Shader::Bind()
{
	glUseProgram(m_program);
}
void Shader::UnBind()
{
	glUseProgram(0);
}
unsigned int Shader::GetProgram()
{
	return m_program;
}
void Shader::Destroy()
{
	glDeleteProgram(m_program);
}