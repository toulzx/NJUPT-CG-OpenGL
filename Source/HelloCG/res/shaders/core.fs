#version 330 core


out vec4 color;


in vec3 ourColor;
in vec2 ourTextCoord;
in float ourTranslateValue;


uniform sampler2D texture0;
uniform sampler2D texture1;


void main()
{

	color = mix(texture(texture0, ourTextCoord), texture(texture1, ourTextCoord), ourTranslateValue); 

}