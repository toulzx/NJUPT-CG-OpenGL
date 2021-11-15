#version 330 core


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 normalVector;


out vec3 ourColor;
out vec3 ourNormalVector;
out vec3 FragPos;				


uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;


void main()
{

	gl_Position =  projection * view * transform * vec4(position, 1.0f);		// ע��˳��
	ourColor = vertexColor;
	ourNormalVector = mat3(transpose(transform)) * normalVector;			// ��ȡ����ת��
	FragPos = vec3(transform * vec4(position, 1.0f));						// ��������ϵ�¹��յĵ�

}