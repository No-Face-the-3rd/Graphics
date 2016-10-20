#pragma once



#ifndef MEOW_OBJECT_H
#define MEOW_OBJECT_H

#include "glm/glm.hpp"
#include "crenderutils.h"

#include <vector>

class obJect
{
public:
	glm::vec3 position, rotation, scale;
	std::string geometry;
	std::vector<std::string> textures;
	glm::vec3 velocity, angularVel;
	float opacity;

	obJect(glm::vec3 pos = glm::vec3(), glm::vec3 rotate = glm::vec3(), glm::vec3 scaLe = glm::vec3(1.0f,1.0f,1.0f), std::string geo = "quad", glm::vec3 vel = glm::vec3(), glm::vec3 angVel = glm::vec3(), float opaque = 1.0f);


	void setTextures(std::string diffuse, std::string normal = "black", std::string specular = "black", std::string glow = "black", std::string vertHeight = "gray");


	glm::mat4 model();

private:
	
};
bool cmpOp(const obJect &a, const obJect &b);

class dirLight
{
public:
	glm::vec3 dir, color;
	bool castShadows;
	glm::mat4 view();
};



#endif
