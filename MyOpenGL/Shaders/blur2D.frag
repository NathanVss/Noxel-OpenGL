#version 150

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D screenTexture;
uniform int screenWidth;
uniform int screenHeight;

uniform int vertical;

bool isWhite(vec4 texture) {

    return texture.r == 1.0 && texture.g == 1.0 && texture.b == 1.0;
}


void main() {

    float intensity = 1.0f;

        vec2 coords = vec2(1.0f / screenWidth * gl_FragCoord.x, 1.0f / screenHeight * gl_FragCoord.y);

    vec4 textureColor = texture(screenTexture, coords);
    if(!isWhite(textureColor)) {

        float blur;
        float vertStep;
        float horizStep;
        float radius = 2;
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
        sum += texture2D(screenTexture, vec2(coords.x - 4.0*blur*horizStep, coords.y - 4.0*blur*vertStep)) * 0.0162162162;
        sum += texture2D(screenTexture, vec2(coords.x - 3.0*blur*horizStep, coords.y - 3.0*blur*vertStep)) * 0.0540540541;
        sum += texture2D(screenTexture, vec2(coords.x - 2.0*blur*horizStep, coords.y - 2.0*blur*vertStep)) * 0.1216216216;
        sum += texture2D(screenTexture, vec2(coords.x - 1.0*blur*horizStep, coords.y - 1.0*blur*vertStep)) * 0.1945945946;

        sum += texture2D(screenTexture, vec2(coords.x, coords.y)) * 0.2270270270;

        sum += texture2D(screenTexture, vec2(coords.x + 1.0*blur*horizStep, coords.y + 1.0*blur*vertStep)) * 0.1945945946;
        sum += texture2D(screenTexture, vec2(coords.x + 2.0*blur*horizStep, coords.y + 2.0*blur*vertStep)) * 0.1216216216;
        sum += texture2D(screenTexture, vec2(coords.x + 3.0*blur*horizStep, coords.y + 3.0*blur*vertStep)) * 0.0540540541;
        sum += texture2D(screenTexture, vec2(coords.x + 4.0*blur*horizStep, coords.y + 4.0*blur*vertStep)) * 0.0162162162;

        // Voila ...
        color = sum;
        // color = textureColor;

    } else {

        color = textureColor;
        // color = vec4(1.0f,0,0,1.0f);
    }

    // color = vec4(fragmentColor.r * intensity, fragmentColor.g * intensity, fragmentColor.b * intensity, fragmentColor.a) * textureColor;

    
}