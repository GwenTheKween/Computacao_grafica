#version 450 core

//Vertex Shader. Takes coordinates from (0,0) to windowSize, and returns between (-1,1) to (1,-1)

layout (location = 0) in vec2 inPosition;
uniform ivec2 windowSize;

void main(){
	gl_Position = vec4((inPosition.x - windowSize.x/2)/(windowSize.x/2),(windowSize.y/2 - inPosition.y)/(windowSize.y/2),0.0 ,1.0);
}
