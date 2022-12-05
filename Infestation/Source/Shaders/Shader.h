#pragma once

#include <string>
#include <GLES3/gl31.h>

std::string file_get_contents(const char* filePath);
void SkipBOM(std::ifstream& in);

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
};
