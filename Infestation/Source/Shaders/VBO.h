#pragma once

#include <GLES3/gl31.h>

class VBO
{
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
