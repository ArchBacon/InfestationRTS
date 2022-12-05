#include <GLES3/gl31.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Shaders/EBO.h"
#include "Shaders/Shader.h"
#include "Shaders/VAO.h"
#include "Shaders/VBO.h"
#include "Window/Input.h"
#include "Window/Window.h"

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f, // Lower left corner
	0.5f, -0.5f, 0.0f, // Lower right corner
	0.0f, 0.5f, 0.0f, // Upper corner
	-0.5f / 2, 0.5f / 2, 0.0f, // Inner left
	0.5f / 2, 0.5f / 2, 0.0f, // Inner right
	0.0f, -0.5f, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main(int argc, char* argv[])
{
    // Create window and initialize EGL context
    const auto window = new MyWindow(640, 480, "Hello Window!");
    const auto input = new Input();

    // Specify the viewport of OpenGL in the window
    glViewport(window->GetPositionX(), window->GetPositionY(), window->GetWidth(), window->GetHeight());

    Shader shaderProgram("../../../Source/Shaders/default.vert", "../../../Source/Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof vertices);
    EBO EBO1(indices, sizeof indices);

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    // Main while loop
    while (window->IsValid())
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        // Poll input events
        input->PollInputEvents(window);

        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        // Bind the VAO so OpenGL knows to use it
        // Draw the triangle using the GL_TRIANGLES primitive
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->SwapBuffers();
    }

    // Cleanup
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    delete input;
    delete window;

    return 0;
}
