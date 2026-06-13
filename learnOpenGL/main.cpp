// CMakeProjectTest.cpp : Defines the entry point for the application.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vec4.hpp>
#include <iostream>
#include <format>
#include <shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <shapes.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, glm::vec4& color);
void CheckForErrors(unsigned int shader); 

Shader* shaderPtr=nullptr;


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 700, "OpenGL Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //window resize callback

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,1000,700);


    Shader ourShader(SHADER_DIR"vertex.glsl", SHADER_DIR"fragment.glsl");
    shaderPtr = &ourShader;
    ourShader.use();
    int width, height;
    glfwGetFramebufferSize(window,&width,&height);
    ourShader.setVec2("resolution", float(width),float(height));

    int sector = 10;
    int stack = 10;
    float radius = 0.5f;
    
    int vertexCount;
    float* vertices = Shapes::createSphereVertices(sector, stack,radius,vertexCount);
    int indicesCount;
    unsigned int* indices = Shapes::createSphereIndices(sector,stack,indicesCount);
    

    //VAO 1
    unsigned int VBO1, VAO1, EBO;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO1); //we bind the vao1
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    //vertex atrrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enables location=0 for the vertex shader 

    ////color atribb
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3* sizeof(float)));
    //glEnableVertexAttribArray(1); //enables location=0 for the vertex shader 


    
   
    

    

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //render wire frame


    glm::vec4 color{ 0.2f, 0.3f, 0.3f, 1.0f };
    glm::mat4 transform = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window)) {
        processInput(window, color);

        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        
        //transformMat4
        float time = glfwGetTime();
        transform = glm::rotate(transform, glm::radians(time*0.0001f), glm::vec3(1.f));
        ourShader.setMat4("transform", transform);
        

       
        glDrawElements(GL_TRIANGLES,indicesCount, GL_UNSIGNED_INT, 0); //the amount of vertices drawn starts at cero finishes at n

       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//Readjust viewport size when user adjusts windowc
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    //std::string s = std::format("Readjusted size to {}x{}",width, height);
    //std::cout << s << "\n";

    shaderPtr->use();
    shaderPtr->setVec2("resolution", float(width),float(height));
}
void processInput(GLFWwindow* window, glm::vec4& color) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        color.r = 1.0f;
    }
}






