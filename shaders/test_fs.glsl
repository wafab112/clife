#version 400

out vec4 frag_color;
in float o_alive;

void main() {
    if (o_alive > 0.5) {
        frag_color = vec4(0.0, 0.0, 1.0, 1.0);
    } else {
        frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    }
}
