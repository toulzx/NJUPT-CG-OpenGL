#version 330 core


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;


out vec3 ourColor;


void main()
{

	gl_Position = vec4(position, 1.0f);
	ourColor = vertexColor;

}