#ifndef PLAYER_H
#define PLAYER_H

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

#include <time.h>
#include <string>

#include "util/camera/camera.h"

class Player
{
private:
	FPSCamera* cam;
	GLFWwindow* window;

	glm::vec3 pos;
	glm::vec3 camPos;
	glm::vec3 look;
	glm::vec3 move;

	bool creativeMode, falling, jumping;
	float jumpTime;
	int winHeight, winWidth;
	unsigned char renderDistance;
	int move_speed;
	float sensitivity;
	float playerHeight;
	double mouseX, mouseY;

public:
	Player(GLFWwindow* window, int winHeight, int winWidth, unsigned char renderDistance = 1, bool creative = true, int moveSpeed = 15);

	void updatePos(glm::vec3 camPos);
	glm::vec3 getPos();
	glm::vec3 getCamPos();
	const glm::vec3& getLook();
	const glm::vec3& getLookAt();
	unsigned char getRenderDistance();
	void setCreative(bool creative);
	void update(double elapsedTime);

	const float& getFOV() const;
	glm::mat4 getViewMatrix() const;
	int getWinHeight() const;
	int getWinWidth() const;

	void setFalling(bool falling);
	bool isFalling() const;
};
#endif