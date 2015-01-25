#version 150

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D lightTexture;
uniform sampler2D spriteTexture;

uniform int shadowCasterWidth;
uniform int shadowCasterHeight;


uniform int screenWidth;
uniform int screenHeight;

uniform float offset;
uniform float sunBias;
uniform float depthGradient;


uniform float screenTopY;
uniform float textureTopY;
uniform float worldHeight;
uniform float blockSize;
uniform float maxDepthLightable;

bool isBlack(vec4 texture) {

    return texture.r == 0 && texture.g == 0 && texture.b == 0;
}

void main() {

    float intensity = 1.0f;
    float _sunBias = sunBias / shadowCasterHeight;
    float _depthGradient = depthGradient / shadowCasterHeight;

    // Coords relative à la texture <=> Distance du bas de la caméra
    // Si on a pixel [0,0.2]
    // On aura coords [0, 0.8]
    vec2 coords;
    coords.x = 1.0f / shadowCasterWidth * gl_FragCoord.x + offset / shadowCasterWidth;
    coords.y = 1 - 1.0f / shadowCasterHeight * gl_FragCoord.y - offset / shadowCasterHeight;

    // Voila ...
    vec4 textureColor = texture(spriteTexture, fragmentUV);
    vec4 obstacleColor = texture(lightTexture, coords);

    // Coordonnées non normalisée par rapport à la texture
    // Si j'ai coords[0, 0.8]
    // On aura absCoords[0, 0.8*720 = 576]
    vec2 absCoords;
    absCoords.x = coords.x * shadowCasterWidth;
    absCoords.y = coords.y * shadowCasterHeight;

    // Coordonnées normalisées du pixel actuel depuis le ciel
    vec2 normCoords;
    normCoords.x = coords.x;
    normCoords.y = coords.y;

    vec4 curTex;
    bool hit = false;
    
    // On parcourt du bas de la texture ciel <=> ( forallx, 0)
    // Jusqu'au pixel actuel
    // On parcourt en absolue car en float pas possible ( archimédien )
    vec2 lastEdge;

    bool exposedToSky = true;

    // Le but est d'avoir le dernier bord en contact avec le ciel.
    // O <- exposedToSKy
    // X <- lastEdge -> !exposedToSKy
    // X <- !exposedToSKy
    // O <- exposedToSKy
    // X <- lastEdge -> !exposedToSKy
    for(int y = 0; y <= absCoords.y; y++) {

        // Reconversion en normalisé en fonction du y actuel
        normCoords.y = 1.0f / shadowCasterHeight * y;
        curTex = texture(lightTexture, normCoords);

        // Premier pixels opaque <=> obstacle
        if(isBlack(curTex)) {
            if(exposedToSky) {}
                lastEdge = normCoords;

            }
            exposedToSky = false;
            hit = true;
        } else {
            exposedToSky = true;
        }

    }

    vec4 light;
    float distFromTopWorld = worldHeight * blockSize - textureTopY + coords.y * shadowCasterHeight;
    float maxDistFromTopWorld = blockSize * maxDepthLightable;

    // Si il est derriere un pixel opaque ET qu'il se situe plus loin que le bias
    if((hit && coords.y >= normCoords.y + _sunBias && isBlack(obstacleColor))) {
        light = vec4(0,0,0,1.0f);

    // Si il se situe dans la zone gradient ET qu'il n'est pas noir ( pas de gradient pour les blocks opaques )
    } else if (distFromTopWorld >= maxDistFromTopWorld && distFromTopWorld <= maxDistFromTopWorld + depthGradient && !isBlack(obstacleColor)) {

        float distToGradient = distFromTopWorld - maxDistFromTopWorld;
        float indice = 1 - distToGradient / depthGradient;
        light = vec4(indice, indice, indice, 255);
    // Si il est plus loin que la limite et plus dans la zone gradient
    } else if(distFromTopWorld > maxDistFromTopWorld + _depthGradient ) {

        light = vec4(0,0,0,1.0f);

    // Sinon ( ciel surface  ou grottes pas dans le gradient ) on mets du blanc
    } else if(!isBlack(obstacleColor)) {

        light = vec4(1.0f,1.0f,1.0f,1.0f);

    // Block opaque à la surface
    } else {
        float indice;
        // Si on enleve cette condition les bords exposés au ciel seront noirs car on aura lastEdge.y = 0 ou indefini
        if(exposedToSky) {
            indice = 1;
        } else {
            float distToHit = coords.y - lastEdge.y;
            indice = 1 - distToHit / _sunBias;
        }
        light = vec4(1.0f * indice, 1.0f * indice, 1.0f * indice, 1.0f);

    }
     color = vec4(fragmentColor.r * intensity, fragmentColor.g * intensity, fragmentColor.b * intensity, fragmentColor.a) * textureColor * light;
    
}