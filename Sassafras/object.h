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
	std::vector<std::string> textures;
	glm::vec3 velocity, angularVel;
private:
	
};

class dirLight
{
	glm::vec3 dir, color;
};



#endif
