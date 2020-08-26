#version 330

in vec3 vColor;
in vec2 texCoords;

out vec4 color;

uniform sampler2D Texture;

void main() {
    vec4 texColor = texture(Texture, texCoords) * vec4(vColor, 1.0);

    if ( texColor.a < 0.1 ) discard;

    color = texColor;
}