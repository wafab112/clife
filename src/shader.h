#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <GL/glew.h>


/**
 * Shader has to be already created with glCreateShader
 * returns true, iff the compilation was successful
 */
bool load_shader(GLuint shader_index, std::string shader_file_name);

#endif
