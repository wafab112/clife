#include <iostream>
#include "GLFW/glfw3.h"

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
        return -1;
    }

    glfwSetErrorCallback(glfw_error_callback);

    auto* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
    if (!window) {
        std::cout << "glfw window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, glfw_key_callback);

    while (!glfwWindowShouldClose(window)) {
        // make fun stuff happen
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
