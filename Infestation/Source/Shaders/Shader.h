#pragma once

#include <string>

class ShaderProgramSource;

class Shader
{
public:
	Shader(const char* path);
	~Shader() = default;

	void Use();
	void Unbind();

private:
	int shaderID;
	ShaderProgramSource ReadShaderFile(const char* path);
	int CompileShader(unsigned int shaderType, const std::string& source);
	void CreateShader(ShaderProgramSource& source);
};