#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoords;

out vec3 vColor;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
    vColor = color;
    texCoords = textureCoords;
}