#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cctype>

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    int success;
    char infoLog[512];

    std::string vertexCode = file_get_contents(vertexFile);
    std::string fragmentCode = file_get_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get reference
    // Attach Vertex Shader source to the Vertex Shader Object
    // Compile the Vertex Shader into machine code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create Fragment Shader Object and get reference
    // Attach Fragment Shader source to the Fragment Shader Object
    // Compile the Fragment Shader into machine code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create Shader Program Object and get its reference
    // Attach the Vertex and Fragment Shaders to the Shader Program
    // Wrap-up/Link all the shaders together into the Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

std::string file_get_contents(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.fail())
    {
        std::cout << "Skipping BOM.\n";
        SkipBOM(file);

        std::cout << "Opened file.\n";
        std::string content;

        std::string line;
        while (std::getline(file, line))
        {
            content += (line + "\n");
        }

        return content += "\0";
    }

    std::cerr << "Error: " << strerror(errno) << "\n";
    return "";
}

void SkipBOM(std::ifstream& in)
{
    char test[3] = { 0 };
    in.read(test, 3);
    if ((unsigned char)test[0] == 0xEF &&
        (unsigned char)test[1] == 0xBB &&
        (unsigned char)test[2] == 0xBF)
    {
        return;
    }
    in.seekg(0);
}
