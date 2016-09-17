#include "camera.h"



#include "timeManager.h"
#include "input.h"

#include <glm\ext.hpp>


void camera::update(const input & input, const timer & timer)
{
	glm::vec3 moveDir = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 right = glm::cross(direction, up);
	up = glm::cross(right, direction);



	if (input.getMouseButtonState(input::RIGHT_MOUSE) == input::DOWN || input.getMouseButtonState(input::RIGHT_MOUSE) == input::PRESS)
	{
		float xPos, yPos;
		input.getDeltaMouse(xPos, yPos);
		direction = glm::rotate(direction, -xPos * rotateSpeed * timer.getDeltaTime(), up);
		direction = glm::rotate(direction, -yPos * rotateSpeed * timer.getDeltaTime(), right);
		
		if (input.getKeyState('Q') == input::DOWN)
			up = glm::rotate(up, -rollSpeed * timer.getDeltaTime(), direction);
		if (input.getKeyState('E') == input::DOWN)
			up = glm::rotate(up, rollSpeed * timer.getDeltaTime(), direction);
		
		input.hideCursor();
		if (input.getKeyState('W') == input::DOWN)
			moveDir += direction;
		if (input.getKeyState('S') == input::DOWN)
			moveDir -= direction;

		if (input.getKeyState('D') == input::DOWN)
			moveDir += right;
		if (input.getKeyState('A') == input::DOWN)
			moveDir -= right;

		if (input.getKeyState(32) == input::DOWN)
			moveDir += up;
		if (input.getKeyState(340) == input::DOWN || input.getKeyState(344) == input::DOWN)
			moveDir -= up;

		if (glm::length(moveDir) >= 0.5f)
		{

			position += glm::normalize(moveDir) * timer.getDeltaTime() * moveSpeed;
		}
	}
	else
	{
		input.showCursor();
	}


}

void camera::lookAt(const glm::vec3 & target)
{
	direction = glm::normalize(target - position);
}

void camera::jumpTo(const glm::vec3 & target)
{
	position = target;
}

glm::mat4 camera::getView() const
{
	return glm::lookAt(position, position + direction,  up);
}

glm::mat4 camera::getProjection() const
{
	return glm::perspective(fov,aspect,near,far);
}
