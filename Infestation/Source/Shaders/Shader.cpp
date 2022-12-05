#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLES2/gl2.h>

struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

Shader::Shader(const char* path)
{
	ShaderProgramSource source = ReadShaderFile(path);
	CreateShader(source);
}

void Shader::Use()
{
	glUseProgram(shaderID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

ShaderProgramSource Shader::ReadShaderFile(const char* path)
{
	ShaderProgramSource source;

	//Open file
	//Check for #shader and #vertexShader tag
	//Save lines to the respective string stream
	std::ifstream file;
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	file.open(path);

	if (file.fail()) {
		printf("File does not exist \n");
	}

	int shaderType = -1;
	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					shaderType = 0;

				if (line.find("fragment") != std::string::npos)
					shaderType = 1;

				continue;
			}

			if (shaderType == 0)
				source.vertexShader += line += "\n";

			if (shaderType == 1)
				source.fragmentShader += line += "\n";

		}
	}
	else
	{
		printf("File not found\n");
	}
	return source;
}

int Shader::CompileShader(unsigned int shaderType, const std::string& source)
{
	const char* src = source.c_str();

	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == false)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error compiling shader" << infoLog << std::endl;
	}

	return shader;
}

void Shader::CreateShader(ShaderProgramSource& source)
{
	shaderID = glCreateProgram();

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, source.vertexShader);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, source.fragmentShader);

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	//glValidateProgram(shaderID);

	int shaderSuccess;
	char shaderInfoLog[512];

	glGetProgramiv(shaderID, GL_LINK_STATUS, &shaderSuccess);
	if (shaderSuccess == false)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, shaderInfoLog);
		std::cout << "Error creating shader program " << shaderInfoLog << std::endl;

	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}