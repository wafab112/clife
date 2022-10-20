#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

static void glfw_error_callback(int error, const char* descr) {
    std::cerr << error << ": " << descr << "\n";
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/**
 * shader has to be already generated
 */
void load_shader(GLuint shader, std::string file_name) {
    std::ifstream file;

    file.open(file_name);

    std::stringstream ss;
    
    std::string line;

    if (!file.is_open()) {
        std::cerr << "File '" << file_name << "' not open." << std::endl;
        return;
    }

    while (getline(file, line)) {
        ss << line << "\n";
    }

    std::string full_shader = ss.str();
    const char * c_shader =  full_shader.data();

    glShaderSource(shader, 1, &c_shader, NULL);
    glCompileShader(shader);
}

int main() {
    if (!glfwInit()) {
        std::cout << "glfw init failed\n";
        return -1;
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
    if (!window) {
        std::cout << "glfw window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, glfw_key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "glew init failed\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    float points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Problem: Durch make run ist cwd in /.../clife/, nicht in /.../clife/build
    //      => shaders Verzeichnis ist falsch in runtime
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    load_shader(vs, "shaders/test_vs.glsl");

    //glShaderSource(vs, 1, &vertex_shader, NULL);
    //glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    load_shader(fs, "shaders/test_fs.glsl");

    //glShaderSource(fs, 1, &fragment_shader, NULL);
    //glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
