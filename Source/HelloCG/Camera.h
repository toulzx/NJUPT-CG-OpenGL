#ifndef Camera_h
#define Camera_h

#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// ˮƽ�ǣ�����Ļ�������ֵ��
const GLfloat DEFAULT_YAW = -90.0f;
// ������	
const GLfloat DEFAULT_PITCH = 0.0f;
// ���򣨿������ţ�
const GLfloat DEFAULT_ZOOM = 45.0f;
// ����ƶ��ٶ�
const GLfloat DEFAULT_SPEED = 6.0f;	
// ��������̶�
const GLfloat DEFAULT_SENSITIVITY = 0.1f;

const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);

const glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

const glm::vec3 DEFAULT_CAMERA_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);


// �������
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera
{
public:
	// ���ڿ�ʹ�ô�Ĭ�ϲ����Ĺ��캯��
	// ʹ�ó�ʼ���б�
	Camera(glm::vec3 nPosition = DEFAULT_POSITION) 
		:
		cameraPosition(nPosition),
		worldUp(DEFAULT_WORLD_UP),
		yaw(DEFAULT_YAW),
		pitch(DEFAULT_PITCH),
		movementSpeed(DEFAULT_SPEED),
		cameraFront(DEFAULT_CAMERA_FRONT), 
		zoom(DEFAULT_ZOOM), 
		mouseSensitivity(DEFAULT_SENSITIVITY)
	{
		this->updateCameraVectors();
	}

	// ����ʹ�ó�ʼ���б��д���ȼ����������֣�
	/*
	Camera(glm::vec3 nPosition = DEFAULT_POSITION) 
	{
		this->position = nPosition;
		this->worldUp = DEFAULT_WORLD_UP;
		this->yaw = DEFAULT_YAW;
		this->pitch = DEFAULT_PITCH;
		this->movementSpeed = DEFAULT_SPEED;
		this->cameraFront = DEFAULT_CAMERA_FRONT;
		this->zoom = DEFAULT_ZOOM;
		this->mouseSensitivity = DEFAULT_SENSITIVITY;
		this->updateCameraVectors();
	}
	*/
	
	// ��ʦ�Ͽ�ʱ��д��
	/*
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat yaw = DEFAULT_YAW,
		GLfloat pitch = DEFAULT_PITCH) :cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), zoom(DEFAULT_ZOOM), movementSpeed(DEFAULT_SPEED), mouseSensitivity(DEFAULT_SENSITIVITY)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}
	*/

	glm::mat4 GetViewMatrix()
	{
		// �����۲����
		return glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
	}

	GLfloat GetZoom()
	{
		return this->zoom;
	}

	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->movementSpeed * deltaTime;

		if (direction == FORWARD)
		{
			this->cameraPosition += this->cameraFront * velocity;
		}
		if (direction == BACKWARD)
		{
			this->cameraPosition -= this->cameraFront * velocity;
		}
		if (direction == LEFT)
		{
			this->cameraPosition -= this->cameraRight * velocity;
		}
		if (direction == RIGHT)
		{
			this->cameraPosition += this->cameraRight * velocity;
		}
	}

	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset)
	{
		xOffset *= this->mouseSensitivity;
		yOffset *= this->mouseSensitivity;

		this->yaw += xOffset;
		this->pitch += yOffset;

		this->updateCameraVectors();

	}

	void ProcessScroll(GLfloat xOffset, GLfloat yOffset)
	{
		if (this->zoom >= 1.0f && this->zoom <= 45.0f)
			this->zoom -= yOffset;
		if (this->zoom <= 1.0f)
			this->zoom = 1.0f;
		if (this->zoom >= DEFAULT_ZOOM)
			this->zoom = 45.0f;
	}


private:
	GLfloat yaw;
	GLfloat pitch;	
	GLfloat zoom;

	GLfloat movementSpeed;
	GLfloat mouseSensitivity;

	glm::vec3 cameraPosition;

	// world axis Y
	glm::vec3 worldUp;

	// (or cameraDirection), camera axis Z
	glm::vec3 cameraFront;
	// camera axis X
	glm::vec3 cameraRight;
	// camera axis Y
	glm::vec3 cameraUp;

	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
		front.y = sin(glm::radians(this->pitch));
		front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));

		this->cameraFront = glm::normalize(front);
		this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->worldUp));
		this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));
	}

};





#endif /* Camera_h */