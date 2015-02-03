#version 150
 
uniform mat4 cameraMatrix;
in vec2 particlePos;
in float particleSize;
in vec4 particleColors;
 
const vec2 pos[] = vec2[4](
  vec2(-0.5,  0.5),
  vec2(-0.5, -0.5),
  vec2(0.5,   0.5),
  vec2(0.5,  -0.5)
);

out vec4 fragmentColor;


void main() {
  vec2 offset = pos[gl_VertexID];
 
  gl_Position = cameraMatrix * vec4(particlePos.x + (offset.x * particleSize) ,
                    	    particlePos.y + (offset.y * particleSize) ,
                            0.0,
                            1.0);
    
  fragmentColor = particleColors;
}