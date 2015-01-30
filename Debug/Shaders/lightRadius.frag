#version 330

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D screenTexture;
uniform int screenTextureWidth;
uniform int screenTextureHeight;



uniform float lightX;
uniform float lightY;
uniform float lightRadius;


bool isWhite(vec4 texture) {

    return texture.r == 1.0 && texture.g == 1.0 && texture.b == 1.0;
}

float getLightIndice() {
    float lightAmount = 0;

    vec2 lightPos = vec2(lightX, screenTextureHeight - lightY);

    float distX = lightPos.x - gl_FragCoord.x;
    distX *= distX;
    float distY = lightPos.y - gl_FragCoord.y;
    distY *= distY;

    float dist = distX + distY;

    float indice = 1 - dist / (lightRadius*lightRadius);
    if(indice < 0) {

        indice = 0;
    }
    lightAmount += indice;

    if(lightAmount > 1) {

        lightAmount = 1;
    }
    return lightAmount;

}

void main() {

    float intensity = 1.0f;


    vec2 coords = vec2(1.0f / screenTextureWidth * gl_FragCoord.x,1.0f / screenTextureHeight * gl_FragCoord.y);
    vec4 textureColor = texture(screenTexture, coords);

    float indice = getLightIndice();
    color = vec4(textureColor.r + indice, textureColor.g + indice, textureColor.b + indice, 1);



}