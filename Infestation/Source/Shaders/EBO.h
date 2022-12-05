#pragma once

#include <GLES3/gl31.h>

class EBO
{
public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
