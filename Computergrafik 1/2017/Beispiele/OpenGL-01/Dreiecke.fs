
#version 450 core  // 420, 330 core , compatibility
in vec4 Color;
layout(location=0) out vec4 fColor;
void main() {
 fColor = Color; 
 }
