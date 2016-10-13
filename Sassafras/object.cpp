#include "object.h"
#include "glm/ext.hpp"

obJect::obJect(glm::vec3 pos, glm::vec3 rotate, glm::vec3 scaLe, std::string geo, glm::vec3 vel, glm::vec3 angVel, float opaque)
{
	position = pos;
	rotation = rotate;
	scale = scaLe;
	geometry = geo;
	for (int i = 0; i < 4; i++)
	{
		textures.push_back("black");
	}
	velocity = vel;
	angularVel = angVel;
	opacity = opaque;
}

void obJect::setTextures(std::string diffuse, std::string normal, std::string specular, std::string glow)
{
	textures.clear();
	textures.push_back(diffuse);
	textures.push_back(normal);
	textures.push_back(specular);
	textures.push_back(glow);
}

glm::mat4 obJect::model()
{
	glm::mat4 ret = glm::mat4();
	ret = glm::translate(ret, position);
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.z, glm::vec3(0, 0, 1));
	ret = glm::scale(scale);
	return ret;
}
