#include "shader.h"

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
