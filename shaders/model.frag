#version 330

in vec3 vColor;
in vec2 texCoords;

out vec4 color;

uniform sampler2D Texture;

uniform int spriteOffsetX;
uniform int spriteOffsetY;

float spriteWidth = 32.0f / 64.0f;
float spriteHeight = 32.0f / 128.0f;

void main() {
    vec2 texCoord = texCoords + vec2(spriteOffsetX * spriteWidth, spriteOffsetY * spriteHeight);

    color = texture(Texture, texCoord) * vec4(vColor, 1.0);
}