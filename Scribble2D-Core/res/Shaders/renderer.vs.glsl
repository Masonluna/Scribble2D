#version 330 core
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main() {
    TexCoords = a_TexCoords;
    gl_Position = projection * model * vec4(0.5, 0.5, 0.0, 1.0);
}
