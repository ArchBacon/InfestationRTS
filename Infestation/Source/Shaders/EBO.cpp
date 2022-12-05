#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    // Bind the EBO specifying it's a Gl_ARRAY_BUFFER
    // Introduce the vertices into the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const
{
    glDeleteBuffers(1, &ID);
}
