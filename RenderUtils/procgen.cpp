#include "procgen.h"
#include "crenderutils.h"
#include "Vertex.h"

#include "glm\gtc\noise.hpp"

Geometry genGrid(unsigned sqr, float dim)
{
	Geometry ret = Geometry();
	unsigned vSize = sqr * sqr, tSize = (sqr - 1) * (sqr - 1) * 6;
	vertex *verts = new vertex[vSize];
	unsigned *tris = new unsigned[tSize];

	unsigned int index = 0;

	for (int r = 0; r < sqr; ++r)
	{
		for (int c = 0; c < sqr; ++c)
		{
			verts[r * sqr + c].position = glm::vec4(((float)c / (sqr - 1.0f) - 0.5f) * dim,0.0f, ((float)r / (sqr - 1.0f) - 0.5f) * dim,1.0f);
			verts[r * sqr + c].texCoord = glm::vec2((float)c / (sqr - 1.0f), (float)r / (sqr - 1.0f));
			verts[r * sqr + c].normal = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

			if (r < sqr - 1 && c < sqr - 1)
			{
				tris[index++] = r * sqr + c;
				tris[index++] = (r + 1) * sqr + c;
				tris[index++] = (r + 1) * sqr + (c + 1);

				tris[index++] = r * sqr + c;
				tris[index++] = (r + 1) * sqr + (c + 1);
				tris[index++] = r * sqr + (c + 1);
			}
		}
	}


	ret = makeGeometry(verts, vSize, tris, tSize);

	delete[] verts;
	delete[] tris;
	
	return ret;
}

Texture genNoise(unsigned sqr, unsigned octaves)
{
	Texture ret = Texture();

	float *noise = new float[sqr * sqr];
	float scale = 1.0f / sqr * 3.0f;

	for (int x = 0; x < sqr; ++x)
	{
		for (int y = 0; y < sqr; ++y)
		{
			float amplitude = 1.0f;
			float persistence = 0.25f;

			noise[y * sqr + x] = 0;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, 0);
				float data = glm::perlin(glm::vec2(x, y) * scale * freq) * 0.5f + 0.5f;
				noise[y * sqr + x] += data * amplitude;
				amplitude *= persistence;
			}
		}
	}

	ret = makeTextureF(sqr, noise);

	delete[] noise;
	

	return ret;
}
