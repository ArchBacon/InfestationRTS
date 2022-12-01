#include <cmath>
#include <GLES3/gl31.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "Window/Input.h"
#include "Window/XWindow.h"

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

int main(int argc, char* argv[])
{
    // Create window and initialize EGL context
    const auto window = new XWindow(640, 480, "Hello Window!");
    const auto input = new Input();

    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    // Specify the viewport of OpenGL in the window
    glViewport(window->GetPositionX(), window->GetPositionY(), window->GetWidth(), window->GetHeight());

    // Create Vertex Shader Object and get reference
    // Attach Vertex Shader source to the Vertex Shader Object
    // Compile the Vertex Shader into machine code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get reference
    // Attach Fragment Shader source to the Fragment Shader Object
    // Compile the Fragment Shader into machine code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    // Attach the Vertex and Fragment Shaders to the Shader Program
    // Wrap-up/Link all the shaders together into the Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create reference containers for the Vertex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a Gl_ARRAY_BUFFER
    // Introduce the vertices into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows hwo to read the VBO
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.00f);
    // Clean the back buffer and assign a new color to it
    glClear(GL_COLOR_BUFFER_BIT);

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
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->SwapBuffers();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    delete input;
    delete window;

    return 0;
}
