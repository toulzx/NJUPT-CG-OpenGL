#version 330 core


out vec4 color;


in vec3 vertexColor;

uniform float colorValue;


void main()
{
	
	//// 作业 1 颜色交替 ---- 使颜色从 (1,0,0,1) => (1,1,0,1)
	color = vec4(vertexColor.x, vertexColor.y + colorValue, vertexColor.z, 1.0f);

}