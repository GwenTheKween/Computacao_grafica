#version 450 core

layout (location = 0) in vec2 inPosition;
uniform ivec2 windowSize;

void main(){
	gl_Position = vec4(inPosition.x/windowSize.x,inPosition.y/windowSize.y,0.0 ,1.0);
}
