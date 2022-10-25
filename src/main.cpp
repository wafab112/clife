#include <iostream>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "Vector.h"
#include "shader.h"
#include "int_types.h"

#include "Chunk.h"

/** TODO
 *      ^ Logging into file (out, err, warn)
 */

static void glfw_error_callback(int error, const char* descr) {
    std::cerr << error << ": " << descr << "\n";
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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

    //glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(50.0f);

    int number_points = 8;
    vec3 points[] = {
        vec3{-0.5f, 0.5f, 0.0f},
        vec3{0.5f, 0.5f, 0.0f},
        vec3{0.5f, -0.5f, 0.0f},
        vec3{-0.5f, -0.5f, 0.0f},
    
        vec3{0.0f, 0.5f, 0.0f},
        vec3{0.5f, 0.0f, 0.0f},
        vec3{0.0f, -0.5f, 0.0f},
        vec3{-0.5f, 0.0f, 0.0f},
    };

    float alive[] = {
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint vec_vbo = 0;
    glGenBuffers(1, &vec_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vec_vbo);
    glBufferData(GL_ARRAY_BUFFER, number_points * sizeof(vec3), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint alive_vbo = 0;
    glGenBuffers(1, &alive_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, alive_vbo);
    glBufferData(GL_ARRAY_BUFFER, number_points * sizeof(float), alive, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);

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

    /*
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
    */

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, 8);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
