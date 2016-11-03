#version 420 core  // 450, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 Color;
void main(){ 
	Color = vColor;

	uniform mat4 ModelViewProjection;
	gl_Position = ModelViewProjection*vPosition;
}
