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
#include <glm/gtx/rotate_vector.hpp>

#include "Shader.h"


#define PI 3.1415926


// 窗口大小
const GLint WIDTH = 800, HEIGHT = 600;

// 存储键盘操作情况
bool keys[1024];

// 实现键盘操作
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);


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

	// 在 GLFW 中注册键盘响应
	glfwSetKeyCallback(window, KeyCallback);
	

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}


	// 开启深度测试
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// 开启混合测试
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");


	// 各面不同颜色的正方体(两个一样的正方体)
	GLfloat vertices[] =
	{		// position1			// color1		
													
		// z = -0.5 的矩形面		// 红色 (1, 0, 0)	
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	
		-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	
													
		// z =  0.5 的矩形面		// 绿色 (0, 1, 0)	
		-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	
		 0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	
		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	
		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	
		-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	
													
		// x = -0.5 的矩形面		// 蓝色 (0, 0, 1)	
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	
													
		// x =  0.5 的矩形面		// 黄色 (1, 1, 0)	
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	
													
		 // y = -0.5 的矩形面	// 紫色 (1, 0, 1)	
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,	
													
		// y =  0.5 的矩形面		// 青色 (0, 1, 1)	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 1.0f,	
		 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 1.0f,	
		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 1.0f,	
		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 1.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 1.0f,	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 1.0f	
	};


	// VAO、VBO 的创建、绑定、设置、解绑
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


	//设置环绕物的起始坐标
	glm::vec3 newPos = glm::vec3(0.0f, 0.0f, -1.0f);


	// 逐帧画图
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);

		// 响应 keyCallback 操作
		glfwPollEvents();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		ourShader.Use();


		glm::mat4 transform;
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		/* 中心正方体（地球） */

		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -2.0f));
		transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(sin(23.5 * PI / 180), cos(23.5 * PI / 180), 0));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		/* 旋转正方体（月球） */

		transform = glm::mat4(1.0f);
		newPos = glm::rotate(newPos, glm::radians(0.05f), glm::vec3(sin(23.5 * PI / 180), cos(23.5 * PI / 180) , 0));
		transform = glm::translate(transform, glm::vec3(newPos.x, newPos.y, newPos.z - 2));
		transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(sin(23.5 * PI / 180), cos(23.5 * PI / 180), 0));
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		
		glfwSwapBuffers(window);
	}

	
	glfwTerminate();


	// 释放
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return 0;

}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// esc 退出
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	// 其它按键若按下则被记录
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}
