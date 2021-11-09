#version 330 core


out vec4 color;


in vec3 ourColor;
in vec2 ourTextCoord;


uniform sampler2D texture0;


void main()
{

	color = texture(texture0, ourTextCoord);

}