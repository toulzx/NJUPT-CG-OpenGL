#version 330 core


out vec4 color;


in vec3 vertexColor;

uniform float colorValue;


void main()
{

	color = vec4(vertexColor.x,
					vertexColor.y + 0.5,
						vertexColor.z,
				1.0f);

}