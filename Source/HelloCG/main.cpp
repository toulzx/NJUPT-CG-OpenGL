#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

// 窗口大小
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

	// 获取显存空间下实际的窗口大小
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	// 设置焦点为当前窗口
	glfwMakeContextCurrent(window);
	

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}


	// 将两着色器文件传入 Shader 头文件
	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");


	// Week5-1 使用点和连接信息来实现原先的矩形（正方形）
	// 定义点和颜色
	GLfloat vertices[] =
	{	// position							// color
		 0.5f,  0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// 右上
		 0.5f, -0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// 右下
		-0.5f, -0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// 左下
		-0.5f,  0.5f,  0.0f,				 1.0f,  0.0f,  0.0f,		// 左上
	};
	// 定义连接信息
	unsigned int indices[] =
	{
		0, 1, 3,				// 第一个三角形
		1, 2, 3					// 第二个三角形
	};

	// 创建顶点正面对象（VAO）、顶点缓存对象（VBO）
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 绑定 VAO、VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 数据传入显卡
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 设置 VAO
	// 对应 core.vs 中此句："layout(location = 0) in vec3 position;" 和本文上述 vertices[] "position" 部分
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// 对应 core.vs 中此句："layout(location = 1) in vec3 ourColor;" 和本文上述 vertices[] "color"部分
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 创建元素缓冲对象（EBO）
	GLuint EBO;
	// 绑定 EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 数据传入显卡
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 解绑定 EBO、VBO、VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// 逐帧画图
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


	// 释放
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;

}