// CMakeProjectTest.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vec4.hpp>
#include <iostream>
#include <format>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, glm::vec4& color);
void CheckForErrors(unsigned int shader); 


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, .5f, .3f,1.0f );\n"
"}\0";

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


    
    //VERTEX SHADER
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    CheckForErrors(vertexShader);

    //FRAGMENT SHADER
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckForErrors(fragmentShader); 

    //SHADER PROGRAM
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    CheckForErrors(shaderProgram); 
    
    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);
    
   

    //setup vertex data
    float tr1[] = {
        -0.5f, -0.5f, 0.0f, 
         -0.5f,  0.5f, 0.0f, 
         0.0f, -0.5f, 0.0f, 
         

    };
    float tr2[] = {
         -0.4f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f,
         0.5f, -0.4f,0.0f,
    };
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    0, 2, 3    // second triangle
    };


    //Setting up 2 different VAO's

    //VAO 1
    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1); //we bind the vao1
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr1), tr1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enables location=0 for the vertex shader 
    glBindBuffer(GL_ARRAY_BUFFER,VBO1);
   

    //VAO 2 
    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2); //we bind the vao2
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr2), tr2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enables location=0 for the vertex shader 
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);


    

  

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //render wire frame


    glm::vec4 color{ 0.2f, 0.3f, 0.3f, 1.0f };

    while (!glfwWindowShouldClose(window)) {
        processInput(window, color);

        glClearColor(color.r, color.g, color.r, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 6); //the amount of vertices drawn starts at cero finishes at 6
        
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES,0, 6); //the amount of vertices drawn starts at cero finishes at 6

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//Readjust viewport size when user adjusts window
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

