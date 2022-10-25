#version 400

in vec3 vp;
in float alive;

out float o_alive;

void main() {
    o_alive = alive;
    gl_Position = vec4(vp, 1.0);
    gl_PointSize = 50.0;
}
