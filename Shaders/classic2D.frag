#version 150

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main() {

    float intensity = 0.5;
    vec4 textureColor = texture(mySampler, fragmentUV);
    color1 = vec4(fragmentColor.r, fragmentColor.g, fragmentColor.b, fragmentColor.a) * textureColor;
    color = color1.xyz * intensity;
}