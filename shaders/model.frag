#version 330

in vec3 vColor;
in vec2 texCoords;

out vec4 color;

uniform sampler2D Texture;

uniform int spriteOffsetX;
uniform int spriteOffsetY;

uniform float spriteWidth;
uniform float spriteHeight;

void main() {
    vec2 texCoord = texCoords + vec2(spriteOffsetX * spriteWidth, spriteOffsetY * spriteHeight);
    vec4 texColor = texture(Texture, texCoord) * vec4(vColor, 1.0);

    if ( texColor.a < 0.1 ) discard;

    color = texColor;
}