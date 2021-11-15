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
#include <GLM/gtx/rotate_vector.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Light.h"


// 窗口大小
const GLint WIDTH = 800, HEIGHT = 600;

// 存储键盘操作情况
bool keys[1024];
// 实现键盘操作
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
// 处理相机前后左右移动
void DoMovement();
// 实现滚轮触发操作
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
// 实现鼠标移动触发操作
void MouseCallback(GLFWwindow* window, double xPos, double yPos);

// 用摄像机坐标对相机视角的实例化
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// 判断是否是第一次获取鼠标位置
bool firstMouse = true;

GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;

// 漫反射参数
const GLfloat DIFFUSE = 0.8f;
// 镜面反射参数
const GLfloat SPECULAR = 0.6f;

// 中心物体移动速度
const GLfloat OBJECT_SPEED = 10.0f;

// 设置光源的坐标
glm::vec3 lightPos = glm::vec3(0.0f, 1.5f, 0.0f);
// 设置中心物体的起始坐标
glm::vec3 ObjectPos = glm::vec3(0.0f, 0.0f, 0.0f);


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

	// 在 GLFW 中注册响应
	glfwSetKeyCallback(window, KeyCallback);
	// glfwSetCursorPosCallback(window, MouseCallback);		// 注释，方便展示效果
	glfwSetScrollCallback(window, ScrollCallback);
	

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
	Shader lightShader = Shader("res/shaders/light.vs", "res/shaders/light.fs");


	// 各面不同颜色的正方体 --- 第 1 个物体
	GLfloat vertices[] =
	{		// position						// color				// normal vector

		// z = -0.5 的矩形面				// 红色 (1, 0, 0)						    
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,			 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,			 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,			1.0f, 0.0f, 0.0f,			 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,			1.0f, 0.0f, 0.0f,			 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,			1.0f, 0.0f, 0.0f,			 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,			 0.0f,  0.0f, -1.0f,

		// z =  0.5 的矩形面				// 绿色 (0, 1, 0)						    
		-0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,			 0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,			 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 0.0f,			 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 0.0f,			 0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 0.0f,			 0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,			 0.0f,  0.0f,  1.0f,

		// x = -0.5 的矩形面				// 蓝色 (0, 0, 1)
		-0.5f,  0.5f,  0.5f,			0.0f, 0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,			0.0f, 0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,			0.0f, 0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,			0.0f, 0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,			0.0f, 0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,			0.0f, 0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,

		// x =  0.5 的矩形面				// 黄色 (1, 1, 0)
		 0.5f,  0.5f,  0.5f,			1.0f, 1.0f, 0.0f,			 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,			1.0f, 1.0f, 0.0f,			 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 1.0f, 0.0f,			 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 1.0f, 0.0f,			 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,			1.0f, 1.0f, 0.0f,			 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,			1.0f, 1.0f, 0.0f,			 1.0f,  0.0f,  0.0f,

		 // y = -0.5 的矩形面			// 紫色 (1, 0, 1)
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 1.0f,			 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 1.0f,			 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,			1.0f, 0.0f, 1.0f,			 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,			1.0f, 0.0f, 1.0f,			 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,			1.0f, 0.0f, 1.0f,			 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 1.0f,			 0.0f, -1.0f,  0.0f,

		// y =  0.5 的矩形面				// 青色 (0, 1, 1)
		-0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 1.0f,			 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 1.0f,			 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 1.0f,			 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 1.0f,			 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,			0.0f, 1.0f, 1.0f,			 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 1.0f,			 0.0f,  1.0f,  0.0f
	};

	// VAO、VBO 的创建、绑定、设置、解绑 --- 第 1 个物体
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// 各面不同颜色的正方体 --- 第 2 个物体
	// VAO、VBO 的创建、绑定、设置、解绑 --- 第 2 个物体
	Light lightModel = Light();


	// 逐帧画图
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);

		// 响应 keyCallback 操作
		glfwPollEvents();
		// 使相机移动
		DoMovement();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		/* 原立方体 */

		ourShader.Use();

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, ObjectPos);
		//transform = glm::rotate(transform, glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		// transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glUniform3f(glGetUniformLocation(ourShader.Program, "LightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(ourShader.Program, "ViewPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform1f(glGetUniformLocation(ourShader.Program, "material.diffuse"), DIFFUSE);
		glUniform1f(glGetUniformLocation(ourShader.Program, "material.specular"), SPECULAR);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		/* 光源立方体 */

		lightShader.Use();

		glm::mat4 transformLight = glm::mat4(1.0f);
		lightPos = glm::rotate(lightPos, glm::radians(0.05f), glm::vec3(0.0f, 0.0f, 1.0f));
		transformLight = glm::translate(transformLight, lightPos);
		transformLight = glm::scale(transformLight, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transformLight));

		glm::mat4 projectionLight = glm::perspective(glm::radians(camera.GetZoom()), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionLight));

		glm::mat4 viewLight = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(viewLight));
		
		lightModel.Draw();


		// 交换缓冲区（双缓冲机制）
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

void DoMovement()
{

	GLfloat currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	// 相机前后左右（w/s/a/d）移动
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	// 物体上下左右（↑/↓/←/→）移动
	if (keys[GLFW_KEY_UP]) {
		ObjectPos.y += deltaTime * OBJECT_SPEED;
	}
	if (keys[GLFW_KEY_DOWN]) {
		ObjectPos.y -= deltaTime * OBJECT_SPEED;
	}
	if (keys[GLFW_KEY_LEFT]) {
		ObjectPos.x -= deltaTime * OBJECT_SPEED;
	}
	if (keys[GLFW_KEY_RIGHT]) {
		ObjectPos.x += deltaTime * OBJECT_SPEED;
	}

}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessScroll(xOffset, yOffset);
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(xOffset, yOffset);
}
