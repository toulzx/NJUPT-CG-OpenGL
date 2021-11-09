#version 330 core


out vec4 color;


in vec3 vertexColor;

uniform float colorValue;


void main()
{
	
	//// ��ҵ 1 ��ɫ���� ---- ʹ��ɫ�� (1,0,0,1) => (1,1,0,1)
	color = vec4(vertexColor.x, vertexColor.y + colorValue, vertexColor.z, 1.0f);

}