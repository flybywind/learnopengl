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
#include <SOIL/SOIL.h>
#include "GLShader.hpp"
#include "GLobj.hpp"
#include "GLTexture.hpp"
#include <iostream>
void glfwErrorCallback(int error, const char *description)
{
    fprintf(stderr, "GLFW error [%d] : %s\n",
                error ,
                description
            );
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main() {
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
//    GLShader shader(vertexShaderSource, STATIC_ARRAY_SIZE(vertexShaderSource),
//                    fragmentShaderSource, STATIC_ARRAY_SIZE(fragmentShaderSource));
    GLShader shader("../vertex_shader", "../fragment_shader");
    
    if (!shader.Link()) {
        const GLchar* err;
        shader.Error(&err);
        std::cerr << "shader failed: " << err << "\n";
        return -1;
    }
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions             // Colors              // Texture Coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 1.0f - 2.0f, // Top Right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 1.0f - 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f - 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f - 2.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    
    GLobj obj1;
    obj1.SetVBO(vertices, STATIC_ARRAY_SIZE(vertices));
    obj1.SetEBO(indices, STATIC_ARRAY_SIZE(indices));
    obj1.SetShader(&shader);
    
    
    obj1.StartBind();
        obj1.SetVertexAttribSize(3);
        obj1.SetVertexAttribStrid(8);
        obj1.SetDrawUsage(GL_STATIC_DRAW);
        obj1.EnableAttrib();
        
        obj1.SetVertexAttribIndex(1);
        obj1.SetVertexAttribOffset(3);
        obj1.EnableAttrib();
    
        obj1.SetVertexAttribIndex(2);
        obj1.SetVertexAttribSize(2);
        obj1.SetVertexAttribOffset(6);
        obj1.EnableAttrib();
    obj1.EndBind();
    
    // texutre
    GLTexture texture("../container.jpg");
    texture.SetParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    texture.SetParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture.SetParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.SetParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.GenMinMap();
    texture.Unbind();
    
    GLTexture texture2("../awesomeface.png");
    texture2.SetParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture2.SetParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture2.SetParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture2.SetParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture2.GenMinMap();
    texture2.Unbind();
    
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 这里修改vertices已经没用了。
//        GLfloat timeValue = glfwGetTime();
//        GLfloat v = (sin(timeValue)+1)/2;
//        vertices[3] = v;
//        vertices[12] = v;
//        vertices[21] = v;
//        obj1.SetVertexAttribIndex(1);
//        obj1.SetVertexAttribOffset(3);
//        obj1.EnableAttrib();
        
        // 在132行不要unbind，这里也不需要重新bind
        //        glBindTexture(GL_TEXTURE_2D, texture);
        
        GLint loc = shader.GetLoc("ourTexture1");
        if (loc >= 0) {
            texture.SwitchUnit(loc, 0);
        } else {
            printf("can't find ourTexture1\n");
        }
        loc = shader.GetLoc("ourTexture2");
        if (loc >= 0) {
            texture2.SwitchUnit(loc, 1);
        } else {
            printf("can't find ourTexture2\n");
        }
        
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