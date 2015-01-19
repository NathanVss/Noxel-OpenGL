#version 150

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main() {

    float intensity = 1.0f;
    vec4 textureColor = texture(mySampler, fragmentUV);
    color = vec4(fragmentColor.r * intensity, fragmentColor.g * intensity, fragmentColor.b * intensity, fragmentColor.a) * textureColor;
}