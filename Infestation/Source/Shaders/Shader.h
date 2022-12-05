#pragma once

#include <GLES3/gl31.h>

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate() const;
    void Delete() const;
};
