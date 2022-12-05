#pragma once

#include <GLES3/gl31.h>
#include "VBO.h"

class VAO
{
public:
    GLuint ID;
    VAO();

    void LinkVBO(VBO& VBO, GLuint layout);
    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
