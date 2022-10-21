#include <iostream>

// Preinstalled .so / .dll / .dylib
#include <GL/glew.h>
// Is built system specifically
#include "GLFW/glfw3.h"

// For file io
#include <fstream>

// For creating a string 
#include <sstream>
#include <string>

#include <cstring>

#include "Vector.cpp"

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
 * returns true, iff the compilation was successful
 */
bool load_shader(GLuint shader_index, std::string shader_file_name) {
    std::ifstream shader_file;

    shader_file.open(shader_file_name);

    if (shader_file.fail()) {
        std::cerr << "Shader '" << shader_file_name << "' failed to open.\n";
        std::cerr << "Error Message: " << std::strerror(errno) << std::endl;
        return false;
    }

    std::stringstream shader_stream;
    std::string line;

    while (getline(shader_file, line)) {
        shader_stream << line << "\n";
    }

    std::string puffer = shader_stream.str();
    const char* shader = puffer.data();

    glShaderSource(shader_index, 1, &shader, NULL);
    glCompileShader(shader_index);

    int shader_compilation_successful = GL_TRUE;
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &shader_compilation_successful);

    if (shader_compilation_successful == GL_FALSE) {
        GLsizei log_length;

        glGetShaderiv(shader_index, GL_INFO_LOG_LENGTH, &log_length);

        char log[log_length];
        glGetShaderInfoLog(shader_index, log_length, NULL, log);

        std::cerr << "Shader log for " << shader_index << " ('" << shader_file_name << "'): " << log << std::endl;

        return false;
    }

    return true;
}

int main() {
    if (!glfwInit()) {
        std::cout << "glfw init failed\n";
        return 1;
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
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, glfw_key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "glew init failed\n";
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    vec3 points[] = {
        vec3 {-0.5f, 0.5f, 0.0f},
        vec3 {0.5f, 0.5f, 0.0f},
        vec3 {0.5f, -0.5f, 0.0f}
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vec3), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Problem: Durch make run ist cwd in /.../clife/, nicht in /.../clife/build
    //      => shaders Verzeichnis ist falsch in runtime
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    if (!load_shader(vs, "shaders/test_vs.glsl")) {
        glfwTerminate();
        return 1;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    if (!load_shader(fs, "shaders/test_fs.glsl")) {
        glfwTerminate();
        return 1;
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    int program_linking_successful = GL_TRUE;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &program_linking_successful);

    if (program_linking_successful == GL_FALSE) {
        GLsizei log_length;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);

        char log[log_length];
        glGetProgramInfoLog(shader_program, log_length, NULL, log);
        std::cerr << "Shader log for " << shader_program << ": " << log << std::endl;
        return 1;
    }

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
