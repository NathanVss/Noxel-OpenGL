#version 150

in vec4 fragmentColor;

out vec4 color;

void main() {


    // Voila ...

    // color = vec4(fragmentColor.r, fragmentColor.g, fragmentColor.b, fragmentColor.a);
    // if(gl_FragCoord.x < 100 && gl_FragCoord.y < 100) {
   		color = vec4(1.0*gl_FragCoord.y/720, 1.0*gl_FragCoord.x/720, 1.0*gl_FragCoord.x/1280, 1.0);

// 
    // }
    
}