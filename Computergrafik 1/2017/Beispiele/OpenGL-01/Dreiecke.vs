
#version 450 core  // 420, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 Color;
void main(){ 
 gl_Position = vPosition;
 Color = vColor;
  }
