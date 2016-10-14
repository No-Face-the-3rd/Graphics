#include "glDraw.h"
#include "glinclude.h"

#include "glm\glm.hpp"
#include "glm\ext.hpp"


void clearFrameBuffer(const frameBuffer & buff)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buff.handle);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void useShaderFlags(const Shader &shader)
{
	if (shader.depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if (shader.faceCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (shader.additiveBlend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
	}
	else
		glDisable(GL_BLEND);

	if (shader.alphaBlend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);
	
}

void tDraw_internal::tDraw_begin(const Shader & shader, const Geometry & geo, const frameBuffer & buff)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buff.handle);
	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);


	useShaderFlags(shader);

	glViewport(0, 0, buff.width, buff.height);

}

void tDraw_internal::tDraw_close(const Shader & shader, const Geometry & geo, const frameBuffer & buff)
{
	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, float val)
{
	glUniform1f(idx, val);
	return 0;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, int val)
{
	glUniform1i(idx, val);
	return 0;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, const Texture & val)
{
	glActiveTexture(GL_TEXTURE0 + texInd);
	glBindTexture(GL_TEXTURE_2D, val.handle);
	glUniform1i(idx, texInd);
	return 1;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, const glm::mat3 & val)
{
	glUniformMatrix3fv(idx, 1, GL_FALSE, glm::value_ptr(val));
	return 0;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, const glm::mat4 & val)
{
	glUniformMatrix4fv(idx, 1, GL_FALSE, glm::value_ptr(val));
	return 0;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, const glm::vec2 & val)
{
	glUniform3fv(idx, 1, glm::value_ptr(val));
	return 0;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, const glm::vec3 & val)
{
	glUniform3fv(idx, 1, glm::value_ptr(val));
	return 0;
}

size_t tDraw_internal::tDraw_format(size_t idx, size_t texInd, const glm::vec4 & val)
{
	glUniform4fv(idx, 1, glm::value_ptr(val));
	return 0;
}



