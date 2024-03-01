// OpenGL_Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include "shader.h"

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};
unsigned int indices[] = {
    0, 1, 2
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render_scene(GLFWwindow* window) {

    glClearColor(0.5f, 0.2f, 0.5f, 1.0);


    glClear(GL_COLOR_BUFFER_BIT);
}

void init_window() {
    // Initialize GLFW
    glfwInit();
    
    // Configure OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    // Configure OpenGL core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main()
{

    init_window();
    
    ///////////////////////////////////////////////////////////////////////////
    // Create GLFW Window
    ///////////////////////////////////////////////////////////////////////////

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

    if(window == NULL){
        std::cout << "Window Creation Failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    ///////////////////////////////////////////////////////////////////////////
    // Initialize GLAD - Load OpenGL function pointers
    ///////////////////////////////////////////////////////////////////////////
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Establish Viewpoprt and window resize callback
    ///////////////////////////////////////////////////////////////////////////
    
    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ///////////////////////////////////////////////////////////////////////////
    // Initialize Virtual Buffer Object (VBO), generate buffer ID
    // Bind VBO to the array buffer and copy vertices to buffer
    ///////////////////////////////////////////////////////////////////////////

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ///////////////////////////////////////////////////////////////////////////
    // Initialize Element Buffer Object (EBO), generate buffer ID
    ///////////////////////////////////////////////////////////////////////////
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    ///////////////////////////////////////////////////////////////////////////
    // Initialize Virtual Array Object (VAO), generate buffer ID
    ///////////////////////////////////////////////////////////////////////////
    unsigned int VAO;
    glGenVertexArrays(1 , &VAO);



    ///////////////////////////////////////////////////////////////////////////
    // Initialize Shader
    ///////////////////////////////////////////////////////////////////////////

    Shader myShader("../shaders/shader.vs", "../shaders/shader.fs");

    // ..:: Initialization code :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) 
    {
        process_input(window);
        render_scene(window);


        // Update color over time

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue);

        myShader.setFloat("offset", greenValue);

        myShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
