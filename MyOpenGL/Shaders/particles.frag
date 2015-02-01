#version 150

in vec4 fragmentColor;

out vec4 color;

void main() {


    // Voila ...

    color = vec4(fragmentColor.r, fragmentColor.g, fragmentColor.b, fragmentColor.a);

    
}