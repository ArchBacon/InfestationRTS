#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    // Bind the VBO specifying it's a Gl_ARRAY_BUFFER
    // Introduce the vertices into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const
{
    glDeleteBuffers(1, &ID);
}
