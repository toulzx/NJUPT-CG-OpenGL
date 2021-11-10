#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

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


	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// ������ϲ���
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");


	// Week7-1 ���治ͬ��ɫ��������
	GLfloat vertices[] =
	{		// position						// color
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,			1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,			1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,			1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,			0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,			0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,			0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,			0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,			0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,			0.0f, 0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,			1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,			1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,			1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,			1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,			1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,			1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,			1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 1.0f,
	};


	// VAO��VBO �Ĵ������󶨡����á����
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// ��֡��ͼ
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();

		//// Week 7-1 ƽ�ơ���ת������ --- BEG

		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::translate(transform, glm::vec3(0.0f, 0.4f, 0.0f));
		transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

		GLuint transLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		//// Week 7-1 ƽ�ơ���ת������ --- END

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
	}

	
	glfwTerminate();


	// �ͷ�
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return 0;

}