uniform float t;
uniform mat4 ModelViewProjectionMatrix;
in vec4 vPos,vCol,vVel;
out vec4 color;
const vec4 g=vec4(0.0,-9.8,0.0);
void main () {
	vec4 p=vec4(vPos);
	p+=t*vVel+t*t*g;
	p.z+=sin(5.0*p.x+t*0.01)*0.25;
	gl_position=ModelViewProjectionMatrix*p;
	color=vCol;
}