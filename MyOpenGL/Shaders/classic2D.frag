#version 150

// in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D spriteTexture;



void main() {

    float intensity = 1.0f;

    // Voila ...
    vec4 textureColor = texture(spriteTexture, fragmentUV);

    color = vec4(fragmentColor.r * intensity, fragmentColor.g * intensity, fragmentColor.b * intensity, fragmentColor.a) * vec4(textureColor.rgba);
   // color = vec4(0,1.0,0,1.0);
    
}