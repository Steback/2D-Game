#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 textureCoords;

out vec3 vCol;

uniform mat4 model;

void main() {
    gl_Position = model * vec4(position, 1.0, 1.0);
    vCol = color;
}