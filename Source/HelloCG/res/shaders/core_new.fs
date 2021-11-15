#version 330 core


out vec4 color;


in vec3 ourNewColor;


void main()
{

	color = vec4(ourNewColor, 1.0f);

}