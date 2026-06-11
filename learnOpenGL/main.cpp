// CMakeProjectTest.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vec4.hpp>
#include <iostream>
#include <format>
#include <shader.h>


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
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, -0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };




    //VAO 1
    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1); //we bind the vao1
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //vertex atrrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enables location=0 for the vertex shader 

    //color atribb
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1); //enables location=0 for the vertex shader 


    glBindVertexArray(VAO1);
   

   


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //render wire frame


    glm::vec4 color{ 0.2f, 0.3f, 0.3f, 1.0f };

    while (!glfwWindowShouldClose(window)) {
        processInput(window, color);

        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        float time = glfwGetTime();
        glm::vec2 displacement(sin(time), cos(time));

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, (float)time, glm::normalize(glm::vec3(displacement, -2.f)));

        displacement *= 0.0;

        ourShader.setMat4("transform", transform);
        ourShader.setVec2("displacement", displacement);

        glDrawArrays(GL_TRIANGLES,0, 3); //the amount of vertices drawn starts at cero finishes at n

       
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

