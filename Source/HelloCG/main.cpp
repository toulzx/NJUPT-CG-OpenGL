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


	// ����λ�ü� Square
	GLfloat vertices[] =
	{	// position						// color
		// first triangle
		 0.5f,  0.5f,  0.0f,			 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.0f,			 1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.0f,			 1.0f,  0.0f,  0.0f,

		// second triangle
		 0.5f, -0.5f,  0.0f,			 1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.0f,			 1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.0f,			 1.0f,  0.0f,  0.0f
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
	// ��Ӧ core.vs �д˾䣺"layout(location = 1) in vec3 ourColor;" �ͱ������� vertices[] "color" ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// ��� VAO��VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// ��֡��ͼ
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ʹ����ɫ������һ��������
		ourShader.Use();

			// ��ҵ 1 ��ɫ����
		float time = glfwGetTime();
		float colorValue = (sin(time) / 2) + 0.5;
		glUniform1f(glGetUniformLocation(ourShader.Program, "colorValue"), colorValue);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	
	glfwTerminate();


	// �ͷ�
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	return 0;

}