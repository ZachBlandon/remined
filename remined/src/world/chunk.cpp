#include "chunk.h"

#include <iostream>

void Chunk::generateVbo()
{
	vbo = (short*)malloc((CHUNKSIZE + 1) * (CHUNKSIZE + 1) * (CHUNKSIZE + 1) * 3 * sizeof(*vbo));

	for (unsigned short yi = 0; yi < x; ++yi)
	{
		for (vboCount = 0; vboCount < y; ++vboCount)
		{
			vbo[3 * (yi * y + vboCount) + 0] = (vboCount / x) + chunkX;
			vbo[3 * (yi * y + vboCount) + 1] = yi + chunkY;
			vbo[3 * (yi * y + vboCount) + 2] = (vboCount % x) + chunkZ;
		}
	}
	vboCount *= x;
}

void Chunk::generateIbo()
{
	ibo = (unsigned short*)malloc((CHUNKSIZE * CHUNKSIZE * CHUNKSIZE * 36) * sizeof(*ibo));
	for (unsigned short i = 0; i < (CHUNKSIZE * x); (++i + 1) % x ? i : ++i)
	{
		for (unsigned short n = i * x; n < (x * (i + 1)) - 1; n -= x + y)
		{
			//negative x
			ibo[iboSize++] = (n);
			ibo[iboSize++] = (n + z);
			ibo[iboSize++] = (n + z + y);
			ibo[iboSize++] = (n + z + y);
			ibo[iboSize++] = (n + y);
			ibo[iboSize++] = (n);
			//negative z
			ibo[iboSize++] = (n);
			ibo[iboSize++] = (n + y);
			ibo[iboSize++] = (n + y + x);
			ibo[iboSize++] = (n + y + x);
			ibo[iboSize++] = (n + x);
			ibo[iboSize++] = (n);
			//negative y
			ibo[iboSize++] = (n);
			ibo[iboSize++] = (n + x);
			ibo[iboSize++] = (n + x + z);
			ibo[iboSize++] = (n + x + z);
			ibo[iboSize++] = (n + z);
			ibo[iboSize++] = (n);
			n += x + y + z;
			//positive z
			ibo[iboSize++] = (n);
			ibo[iboSize++] = (n - x);
			ibo[iboSize++] = (n - x - y);
			ibo[iboSize++] = (n - x - y);
			ibo[iboSize++] = (n - y);
			ibo[iboSize++] = (n);
			//positive y
			ibo[iboSize++] = (n);
			ibo[iboSize++] = (n - z);
			ibo[iboSize++] = (n - z - x);
			ibo[iboSize++] = (n - z - x);
			ibo[iboSize++] = (n - x);
			ibo[iboSize++] = (n);
			//positive x
			ibo[iboSize++] = (n);
			ibo[iboSize++] = (n - y);
			ibo[iboSize++] = (n - y - z);
			ibo[iboSize++] = (n - y - z);
			ibo[iboSize++] = (n - z);
			ibo[iboSize++] = (n);
		}
	}
}

void Chunk::printVbo()
{
	std::cout << "VBO expected: " << (CHUNKSIZE + 1) * (CHUNKSIZE + 1) * (CHUNKSIZE + 1) << std::endl;
	std::cout << "VBO: " << vboCount << std::endl;
	for (int i = 0; i < vboCount * 3; ++i)
	{
		if (!(i % 3))
			std::cout << std::endl << "[" << (int)i / 3 << "]: ";
		std::cout << vbo[i] << ", ";
	}
	std::cout << std::endl;
}

void Chunk::printIbo()
{
	std::cout << "IBO expected: " << CHUNKSIZE * CHUNKSIZE * CHUNKSIZE * 12 << std::endl;
	std::cout << "IBO: " << iboSize / 3 << std::endl;
	for (int i = 0; i < iboSize; ++i)
	{
		if (!(i % 3))
			std::cout << std::endl << "[" << i / 3 << "]: ";
		std::cout << ibo[i] << ", ";
	}
	std::cout << std::endl;
}

Chunk::Chunk(short chunkX, short chunkY, short chunkZ)
	:chunkX(chunkX* CHUNKSIZE), chunkY(chunkY* CHUNKSIZE), chunkZ(chunkZ* CHUNKSIZE), vboCount(0), iboSize(0), x(CHUNKSIZE + 1), y((CHUNKSIZE + 1)* (CHUNKSIZE + 1)), z(1)
{
	generateVbo();
	generateIbo();
}

const void* Chunk::getVbo() const
{
	return vbo;
}

unsigned int Chunk::getSizeOfVbo() const
{
	return vboCount * 3 * sizeof(*vbo);
}

const unsigned short* Chunk::getIbo()
{
	return ibo;
}

unsigned int Chunk::getSizeOfIbo()
{
	return (unsigned int)iboSize;
}