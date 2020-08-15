#version 330

in vec3 vColor;
in vec2 texCoords;

out vec4 color;

uniform sampler2D Texture;

void main() {

    color = texture(Texture, texCoords) * vec4(vColor, 1.0);
}