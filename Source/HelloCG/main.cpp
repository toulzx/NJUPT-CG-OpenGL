#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//SOIL2
#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

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


	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");


	// ʹ�õ��������Ϣ����	// Week5-2 �����������
	GLfloat vertices[] =
	{	// position					// color						// texture coords
		 0.5f,  0.5f,  0.0f,		 1.0f,  0.0f,  0.0f,			 1.0f, 1.0f,			// ����
		 0.5f, -0.5f,  0.0f,		 1.0f,  0.0f,  0.0f,			 1.0f, 0.0f,			// ����
		-0.5f, -0.5f,  0.0f,		 1.0f,  0.0f,  0.0f,			 0.0f, 0.0f,			// ����
		-0.5f,  0.5f,  0.0f,		 1.0f,  0.0f,  0.0f,			 0.0f, 1.0f,			// ����
	};
	unsigned int indices[] =
	{
		0, 1, 3,				// ��һ��������
		1, 2, 3					// �ڶ���������
	};


	// VAO��VBO��EBO �Ĵ������󶨡����á����
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// ���� 2 ά������ͼ
	GLuint texture0, texture1;
	int textureWidth0, textureHeight0, textureWidth1, textureHeight1;
	
	unsigned char* textureImage0 = SOIL_load_image("res/images/T_Reflection_Tiles_D.BMP", &textureWidth0, &textureHeight0, 0, SOIL_LOAD_RGBA);
	unsigned char* textureImage1 = SOIL_load_image("res/images/T_TilingNoise03_M.BMP", &textureWidth1, &textureHeight1, 0, SOIL_LOAD_RGBA);

	// ���ɵ� 1 ������
	// ���ɡ�������
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// �������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// ����������ء�����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth0, textureHeight0, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage0);
	glGenerateMipmap(GL_TEXTURE_2D);
	// ���
	glBindTexture(GL_TEXTURE_2D, 0);

	//// ��ҵ 2 ������任 ---- BEG
	 
	// ͬ����һ����Σ����ɵ� 2 ������
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth1, textureHeight1, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage1);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//// ��ҵ 2 ������任 ---- END


	// ��֡��ͼ
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		ourShader.Use();


		//// ��ҵ 2 ������任 ---- BEG

		float time = glfwGetTime();
		float translateValue = fmodf(time, 10.0f) / 10.0f;

		if (((int)time / 10) % 2)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(ourShader.Program, "texture0"), 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(ourShader.Program, "texture1"), 1);
		} else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(ourShader.Program, "texture0"), 1);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(ourShader.Program, "texture1"), 0);
		}

		glUniform1f(glGetUniformLocation(ourShader.Program, "translateValue"), translateValue);

		//// ��ҵ 2 ������任 ---- END

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glfwSwapBuffers(window);
	}

	
	glfwTerminate();


	// �ͷ�
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture0);

	return 0;

}