//
//  main.cpp
//  Shaders
//
//  Created by flybywind on 16/5/2.
//  Copyright © 2016年 flybywind. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLShader.hpp"
#include "GLobj.hpp"

#include <iostream>
void glfwErrorCallback(int error, const char *description)
{
    fprintf(stderr, "GLFW error [%d] : %s\n",
                error ,
                description
            );
}
// Shaders
const GLchar* vertexShaderSource[] = {
    "layout (location = 0) in vec3 position;",
    "void main()",
    "{",
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);",
    "}"
};
const GLchar* fragmentShaderSource[] = {
    "out vec4 color;",
    "uniform vec4 ourColor;",
    "void main()",
    "{",
        "color = ourColor;",
    "}"
};



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main(int argc, const char * argv[]) {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    glfwSetErrorCallback(glfwErrorCallback);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // GLEW负责管理每个平台上应该调用哪个函数指针，所以在调用openGL之前，先初始化它
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);
    
    // Build and compile our shader program
    // Vertex shader
    strncpy(GLShader::Version, "410", 3);
    GLShader shader(vertexShaderSource, STATIC_ARRAY_SIZE(vertexShaderSource),
                    fragmentShaderSource, STATIC_ARRAY_SIZE(fragmentShaderSource));
    if (!shader.Link()) {
        const GLchar* err;
        shader.Error(&err);
        std::cerr << "shader failed: " << err << "\n";
        return -1;
    }
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,  // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f, // bottom left
    };
    
    GLobj obj1;
    obj1.SetVBO(vertices, STATIC_ARRAY_SIZE(vertices));
    obj1.SetVertexAttribSize(3);
    obj1.SetDrawUsage(GL_STATIC_DRAW);
    obj1.SetShader(&shader);
    obj1.Bind();
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        shader.Uniform4f("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
        // Draw our first triangle
        obj1.Draw(GL_TRIANGLES);
        
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}