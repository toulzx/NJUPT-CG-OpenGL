#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

// ���ڴ�С
const GLint WIDTH = 800, HEIGHT = 600;


int main()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
	
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ��ȡ�Դ�ռ���ʵ�ʵĴ��ڴ�С
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	// ���ý���Ϊ��ǰ����
	glfwMakeContextCurrent(window);
	

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}


	// ������ɫ���ļ����� Shader ͷ�ļ�
	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");


	// Week5-1 ʹ�õ��������Ϣ��ʵ��ԭ�ȵľ��Σ������Σ�
	// ��������ɫ
	GLfloat vertices[] =
	{	// position							// color
		 0.5f,  0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// ����
		 0.5f, -0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// ����
		-0.5f, -0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// ����
		-0.5f,  0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// ����
	};
	// ����������Ϣ
	unsigned int indices[] =
	{
		0, 1, 3,				// ��һ��������
		1, 2, 3					// �ڶ���������
	};

	// ���������������VAO�������㻺�����VBO��
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// �� VAO��VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���ݴ����Կ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���� VAO
	// ��Ӧ core.vs �д˾䣺"layout(location = 0) in vec3 position;" �ͱ������� vertices[] "position" ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��Ӧ core.vs �д˾䣺"layout(location = 1) in vec3 ourColor;" �ͱ������� vertices[] "color"����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// ����Ԫ�ػ������EBO��
	GLuint EBO;
	// �� EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// ���ݴ����Կ�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ��� EBO��VBO��VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// ��֡��ͼ
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	
	glfwTerminate();


	// �ͷ�
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;

}