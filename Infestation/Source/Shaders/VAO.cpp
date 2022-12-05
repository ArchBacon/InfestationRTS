#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
    
}

void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
    VBO.Bind();
    // Configure the Vertex Attribute so that OpenGL knows hwo to read the VBO
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);

    VBO.Unbind();
}

void VAO::Bind() const
{
    // Make the VAO the current Vertex Array Object
    glBindVertexArray(ID);
}

void VAO::Unbind() const
{
    // Make the VAO the current Vertex Array Object
    glBindVertexArray(0);
}

void VAO::Delete() const
{
    glDeleteVertexArrays(1, &ID);
}
