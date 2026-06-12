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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, glm::vec4& color);
void CheckForErrors(unsigned int shader); 




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
   

    //setup vertex data
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };




    //VAO 1
    unsigned int VBO1, VAO1, EBO;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO1); //we bind the vao1
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //vertex atrrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enables location=0 for the vertex shader 

    //color atribb
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1); //enables location=0 for the vertex shader 

    //texCoords
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); //enables location=0 for the vertex shader 


    
   
    //texture 
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(RESOURCES_DIR"container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //render wire frame


    glm::vec4 color{ 0.2f, 0.3f, 0.3f, 1.0f };

    while (!glfwWindowShouldClose(window)) {
        processInput(window, color);

        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
       
        glDrawElements(GL_TRIANGLES,sizeof(indices), GL_UNSIGNED_INT, 0); //the amount of vertices drawn starts at cero finishes at n

       
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
}
void processInput(GLFWwindow* window, glm::vec4& color) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        color.r = 1.0f;
    }
}


void CheckForErrors(unsigned int shader) {
    int succes;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);

    if (!succes) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

}

