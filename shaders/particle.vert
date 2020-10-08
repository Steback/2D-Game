#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCords;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;
uniform vec2 offset;
uniform vec4 color;

void main() {
    float scale = 10.0f;
    TexCoords = textureCords;
    ParticleColor = color;
    gl_Position = projection * view * vec4((position * scale) + offset, 0.0, 1.0);
}