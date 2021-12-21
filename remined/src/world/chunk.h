#ifndef CHUNK_H
#define CHUNK_H
#define CHUNKSIZE 16

class Chunk
{
private:
	short* vbo;
	unsigned int iboSize;
	unsigned short* ibo;
	unsigned short vboCount;
	short chunkX, chunkY, chunkZ;
	const unsigned short x, y, z;

	void generateVbo();
	void generateIbo();
	void printVbo();
	void printIbo();

public:
	Chunk(short chunkX, short chunkY, short chunkZ);
	const void* getVbo() const;
	unsigned int getSizeOfVbo() const;
	const unsigned short* getIbo();
	unsigned int getSizeOfIbo();
};

#endif
