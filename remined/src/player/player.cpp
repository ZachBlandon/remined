#include "player.h"
#include <iostream>

Player::Player(GLFWwindow* window, int winWidth, int winHeight, unsigned char renderDistance, bool creative, int moveSpeed)
	:window(window), winWidth(winWidth), winHeight(winHeight), renderDistance(renderDistance), creativeMode(creative), move_speed(moveSpeed),
	sensitivity(0.15f), playerHeight(3.25), falling(false), jumping(false), jumpTime(0.0f)
{
	cam = new FPSCamera(glm::vec3(1.0f, 16.0f + playerHeight, 1.0f));
}

void Player::updatePos(glm::vec3 camPos)
{
	this->camPos = camPos;
}

glm::vec3 Player::getPos()
{
	return pos;
}

glm::vec3 Player::getCamPos()
{
	return camPos;
}

const glm::vec3& Player::getLook()
{
	return cam->getLook();
}

const glm::vec3& Player::getLookAt()
{
	return cam->getTargetPos();
}

unsigned char Player::getRenderDistance()
{
	return renderDistance;
}

void Player::setCreative(bool creative)
{
	creativeMode = creative;
}

const float& Player::getFOV() const
{
	return cam->getFOV();
}

glm::mat4 Player::getViewMatrix() const
{
	return cam->getViewMatrix();
}

int Player::getWinHeight() const
{
	return winHeight;
}

int Player::getWinWidth() const
{
	return winWidth;
}

void Player::setFalling(bool falling)
{
	this->falling = falling;
}

bool Player::isFalling() const
{
	return falling;
}

void Player::update(double elapsedTime)
{
	glfwGetCursorPos(window, &mouseX, &mouseY);
	cam->rotate((float)(winWidth / 2.0 - mouseX) * sensitivity, (float)(winHeight / 2.0 - mouseY) * sensitivity);
	glfwSetCursorPos(window, winWidth / 2.0, winHeight / 2.0);

	std::cout << "Falling: " << std::boolalpha << falling << std::endl;
	std::cout << "Jumping: " << std::boolalpha << jumping << std::endl;
	std::cout << "Pos y: " << pos.y << std::endl;

	if (!jumping)
	{
		if (falling)
		{
			cam->move(glm::vec3(0, -0.125, 0));
		}
	}
	else
	{
		cam->move(glm::vec3(0, 0.125, 0));
		if ((jumpTime += 0.125) >= 1.6f)
		{
			jumping = false;
			jumpTime = 0.0f;
		}
	}

	camPos = cam->getPos();
	pos = camPos;
	pos.y -= playerHeight;
	move = look = cam->getLook();
	move.y = 0;

	move_speed = 10;
	if (creativeMode) {
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			cam->move(move_speed * (float)elapsedTime * glm::vec3(0, 1, 0));
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cam->move(move_speed * (float)elapsedTime * glm::vec3(0, -1, 0));
	}
	else
	{
		if (!falling)
		{
			if (!jumping && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
				jumping = true;
				//cam->move(move_speed * (float)elapsedTime * glm::vec3(0, 0.3, 0));
			//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				//cam->move(move_speed * (float)elapsedTime * glm::vec3(0, -1, 0));
		}
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		move_speed = 20;
	else
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			move_speed = 10;
		else
			move_speed = 15;
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam->move(move_speed * (float)elapsedTime * move);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->move(move_speed * (float)elapsedTime * -move);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->move(move_speed * (float)elapsedTime * -cam->getRight());
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->move(move_speed * (float)elapsedTime * cam->getRight());
}
