#pragma once




#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>

class camera
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	float aspect, fov, near, far;

	float moveSpeed, rotateSpeed, rollSpeed;

public:
	camera(float aspect = 16.0f / 9.0f, float fov = 45.0f, float near = 0.1f, float far = 50.0f) : aspect(aspect), fov(fov), near(near), far(far), direction(0, 0, 1), moveSpeed(20.0f), rotateSpeed(50.0f), up(0,1,0), rollSpeed(5.0f)
	{
	}

	void update(const class input &input, const class timer &timer);

	void lookAt(const glm::vec3 &target);
	void jumpTo(const glm::vec3 &target);

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
};



#endif
