#version 330 core


layout(location = 2) in vec3 newPosition;
layout(location = 3) in vec3 newVertexColor;


out vec3 ourNewColor;


uniform mat4 newTransform;
uniform mat4 newProjection;


void main()
{

	gl_Position = newProjection * newTransform * vec4(newPosition, 1.0f);
	ourNewColor = newVertexColor;

}