#include "Shader.h"
#include <string>

const char* vertexShaderSource = "#version 300 es\n"
"precision mediump float;\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 300 es\n"
"precision mediump float;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = vertexShaderSource;
    std::string fragmentCode = fragmentShaderSource;

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get reference
    // Attach Vertex Shader source to the Vertex Shader Object
    // Compile the Vertex Shader into machine code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get reference
    // Attach Fragment Shader source to the Fragment Shader Object
    // Compile the Fragment Shader into machine code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    // Attach the Vertex and Fragment Shaders to the Shader Program
    // Wrap-up/Link all the shaders together into the Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() const
{
    glUseProgram(ID);
}

void Shader::Delete() const
{
    glDeleteProgram(ID);
}
