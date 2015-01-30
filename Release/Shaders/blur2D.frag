#version 330

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D screenTexture;
uniform int screenTextureWidth;
uniform int screenTextureHeight;

uniform int screenWidth;
uniform int screenHeight;

uniform int vertical;
uniform int invertY;
uniform float offset;


uniform float sunIndice;


bool isWhite(vec4 texture) {

    return texture.r == 1.0 && texture.g == 1.0 && texture.b == 1.0;
}

void main() {

    float intensity = 1.0f;


        vec2 coords = vec2(1.0f / screenTextureWidth * gl_FragCoord.x + offset / screenTextureWidth, 1.0f / screenTextureHeight * gl_FragCoord.y + offset / screenTextureHeight);

        if(invertY == 1) {

            coords.y = 1.0f - coords.y;
        }

    vec4 textureColor = texture(screenTexture, coords);
    if(!isWhite(textureColor)) {
        float blur;
        float vertStep;
        float horizStep;
        float radius = 2.5;
        if(vertical == 1) {
        	blur = radius / screenHeight;
        	vertStep = 1.0f;
        	horizStep = 0.0f;
        } else {
        	blur = radius / screenWidth;
          	vertStep = 0.0f;
        	horizStep = 1.0f;
        }


        vec4 sum = vec4(0.0);
        // sum += texture2D(screenTexture, vec2(coords.x - 4.0*blur*horizStep, coords.y - 4.0*blur*vertStep)) * 0.0162162162;
        // sum += texture2D(screenTexture, vec2(coords.x - 3.0*blur*horizStep, coords.y - 3.0*blur*vertStep)) * 0.0540540541;
        // sum += texture2D(screenTexture, vec2(coords.x - 2.0*blur*horizStep, coords.y - 2.0*blur*vertStep)) * 0.1216216216;
        // sum += texture2D(screenTexture, vec2(coords.x - 1.0*blur*horizStep, coords.y - 1.0*blur*vertStep)) * 0.1945945946;

        // sum += texture2D(screenTexture, vec2(coords.x, coords.y)) * 0.2270270270;

        // sum += texture2D(screenTexture, vec2(coords.x + 1.0*blur*horizStep, coords.y + 1.0*blur*vertStep)) * 0.1945945946;
        // sum += texture2D(screenTexture, vec2(coords.x + 2.0*blur*horizStep, coords.y + 2.0*blur*vertStep)) * 0.1216216216;
        // sum += texture2D(screenTexture, vec2(coords.x + 3.0*blur*horizStep, coords.y + 3.0*blur*vertStep)) * 0.0540540541;
        // sum += texture2D(screenTexture, vec2(coords.x + 4.0*blur*horizStep, coords.y + 4.0*blur*vertStep)) * 0.0162162162;

        sum += texture2D(screenTexture, vec2(coords.x - 16.0*blur*horizStep, coords.y - 16.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 15.0*blur*horizStep, coords.y - 15.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 14.0*blur*horizStep, coords.y - 14.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 13.0*blur*horizStep, coords.y - 13.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 12.0*blur*horizStep, coords.y - 12.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 11.0*blur*horizStep, coords.y - 11.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 10.0*blur*horizStep, coords.y - 10.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 9.0*blur*horizStep, coords.y - 9.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 8.0*blur*horizStep, coords.y - 8.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 7.0*blur*horizStep, coords.y - 7.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 6.0*blur*horizStep, coords.y - 6.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 5.0*blur*horizStep, coords.y - 5.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 4.0*blur*horizStep, coords.y - 4.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 3.0*blur*horizStep, coords.y - 3.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 2.0*blur*horizStep, coords.y - 2.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x - 1.0*blur*horizStep, coords.y - 1.0*blur*vertStep)) * 0.030;

        sum += texture2D(screenTexture, vec2(coords.x, coords.y)) * 0.04;

        sum += texture2D(screenTexture, vec2(coords.x + 1.0*blur*horizStep, coords.y + 1.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 2.0*blur*horizStep, coords.y + 2.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 3.0*blur*horizStep, coords.y + 3.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 4.0*blur*horizStep, coords.y + 4.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 5.0*blur*horizStep, coords.y + 5.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 6.0*blur*horizStep, coords.y + 6.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 7.0*blur*horizStep, coords.y + 7.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 8.0*blur*horizStep, coords.y + 8.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 9.0*blur*horizStep, coords.y + 9.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 10.0*blur*horizStep, coords.y + 10.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 11.0*blur*horizStep, coords.y + 11.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 12.0*blur*horizStep, coords.y + 12.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 13.0*blur*horizStep, coords.y + 13.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 14.0*blur*horizStep, coords.y + 14.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 15.0*blur*horizStep, coords.y + 15.0*blur*vertStep)) * 0.030;
        sum += texture2D(screenTexture, vec2(coords.x + 16.0*blur*horizStep, coords.y + 16.0*blur*vertStep)) * 0.030;

        // Voila ...
        if(vertical == 1) {


            color = vec4(sum.rgb * sunIndice, sum.a);

        } else {
            color = sum;


        }

    } else {

        if(vertical == 1) {
            color = vec4(textureColor.rgb * sunIndice, textureColor.a);


        } else {
            color = textureColor;


        }
    }


    
}