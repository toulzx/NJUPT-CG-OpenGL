#version 330 core


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 textCoord;


out vec3 ourColor;
out vec2 ourTextCoord;


void main()
{

	gl_Position = vec4(position, 1.0f);
	ourColor = vertexColor;
	ourTextCoord = vec2(textCoord.x, 1 - textCoord.y);

}