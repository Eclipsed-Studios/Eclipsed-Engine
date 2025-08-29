#include "Editor.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "TemporarySettingsSingleton.h"

#include <stdio.h>

#include <vector>
#include <iostream>

struct SpriteVertex
{
    float posX;
    float posY;

    float colR;
    float colG;
    float colB;
};

// 4 vertices
static SpriteVertex vertices[]{
    {0, 0, 1, 0, 0},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {1, 1, 1, 1, 0}};

// 6 indices
static unsigned indices[]{
    0, 1, 2,
    2, 1, 3};

void WindowChangeDimenstions(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    TemporarySettingsSingleton::Get().SetResolution(width, height);
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

namespace ENGINE_NAMESPACE
{
    ErrorCode Editor::Init()
    {
        glfwSetErrorCallback(error_callback);

        int iResult;

        // GLFW initialization
        {
            iResult = glfwInit();
            if (!iResult)
                return ErrorCode::GLFW_FAILED_TO_INITILIZE;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        }

        // Window creation
        {
            float x = TemporarySettingsSingleton::Get().GetResultionX();
            float y = TemporarySettingsSingleton::Get().GetResultionY();
            const char *gameTitle = TemporarySettingsSingleton::Get().GetGameTitle();

            myWindow = glfwCreateWindow(x, y, gameTitle, nullptr, nullptr);
            if (!myWindow)
                return ErrorCode::GLFW_WINDOW_FAILED_TO_CREATE;

            TemporarySettingsSingleton::Get().myWindow = myWindow;
        }

        // Set context to current context
        glfwMakeContextCurrent(myWindow);

        // Glad initialization
        {
            iResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!iResult)
                return ErrorCode::GLAD_FAILED_TO_INITILIZE;
        }

        // Setup Window size change callback
        {
            glfwSetFramebufferSizeCallback(myWindow, WindowChangeDimenstions);
        }

        // Extra GLFW settings
        {
            glfwSwapInterval(TemporarySettingsSingleton::Get().GetNumRenderBuffers());
        }

        // Temporary sprite making
        {
            {
                static const char *vertex_shader_text =
                    "#version 410 core\n"
                    "layout (location = 0) in vec2 aPos;\n"
                    "layout (location = 1) in vec3 aColor;\n"
                    "out vec3 color;\n"
                    "void main() {\n"
                    "   color = aColor;\n"
                    "   gl_Position = vec4( aPos, 0.0, 1.0 );\n"
                    "}";

                static const char *fragment_shader_text =
                    "#version 410 core\n"
                    "in vec3 color;"
                    "out vec4 frag_colour;"
                    "void main() {"
                    "  frag_colour = vec4(color, 1.0 );"
                    "}";

                glGenBuffers(1, &vertexBuffer);
                glGenBuffers(1, &indexBuffer);

                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                glGenVertexArrays(1, &indexVertexBuffer);
                glBindVertexArray(indexVertexBuffer);

                glBindBuffer(GL_ARRAY_BUFFER, (GLuint)vertexBuffer);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)indexBuffer);

                {
                    // glVertexAttribPointer(shader layout index, total number of floats/ints/bools etc, GL_[your type], GL_FALSE, vertex stride, offset from last layout position)

                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void *)0);
                    glEnableVertexAttribArray(1);
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void *)(sizeof(float) * 2));
                }

                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertex_shader_text, NULL);
                glCompileShader(vertexShader);

                GLint success;

                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    GLint logLength = 0;
                    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

                    std::vector<char> log(logLength);
                    glGetShaderInfoLog(vertexShader, logLength, nullptr, log.data());

                    std::cerr << "Vertex shader compilation failed:\n" << log.data() << std::endl;
                    throw("Vertex shader compilation failed");
                }

                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragment_shader_text, NULL);
                glCompileShader(fragmentShader);

                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    GLint logLength = 0;
                    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

                    std::vector<char> log(logLength);
                    glGetShaderInfoLog(fragmentShader, logLength, nullptr, log.data());

                    std::cerr << "Pixel/Fragment shader compilation failed:\n" << log.data() << std::endl;
                    throw("Pixel/Fragment shader compilation failed");
                }

                program = glCreateProgram();
                glAttachShader(program, vertexShader);
                glAttachShader(program, fragmentShader);
                glLinkProgram(program);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            }
        }

        return ErrorCode::SUCCESS;
    }

    void Editor::Begin()
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Editor::Update()
    {
    }

    void Editor::Render()
    {
        float matrix[] = {1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1};

        glUseProgram(program);
        glBindVertexArray(indexVertexBuffer);
        // glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, (const GLfloat *)matrix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Editor::End()
    {
        glfwSwapBuffers(myWindow);
    }
}