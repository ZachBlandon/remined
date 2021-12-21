#include "world.h"
#include "chunk.h"

#include "glm/gtc/matrix_transform.hpp"

double World::worldTime;
double World::lastTime;

World::World(Player* player)
	: player(player), shader(new Shader("res/shaders/cube_texture.shader")), texture(new Texture("res/textures/grid.jpg")),
		va(new VertexArray), layout(new VertexBufferLayout), renderer(new Renderer)
{
	worldTime = glfwGetTime();
	generateChunks();
	layout->push<short>(3);
	shader->bind();
	texture->bind();
}

void World::generateChunks()
{
	for (char i = player->getRenderDistance() * -1; i <= player->getRenderDistance(); ++i)
	{
		for (char j = player->getRenderDistance() * -1; j <= player->getRenderDistance(); ++j)
		{
			Chunk* c = new Chunk(i, 0, j);
			chunks.push_back(c);
			vb.push_back(new VertexBuffer(c->getVbo(), c->getSizeOfVbo()));
			ib.push_back(new IndexBuffer(c->getIbo(), c->getSizeOfIbo()));
		}
	}
}
World* World::getInstance(Player* player) {
	static World* instance = new World(player);
	return instance;
}

glm::vec3 World::getWorldPos(glm::vec3 playerPos)
{
	short x, y, z;
	x = ((short)playerPos.x / CHUNKSIZE) * (player->getRenderDistance() * 2 + 1);
	y = (short)playerPos.y / CHUNKSIZE;
	z = (short)playerPos.z / CHUNKSIZE;

	int center = (player->getRenderDistance() * 2 + 1) * (player->getRenderDistance() * 2 + 1) / 2;
	//int offset =(CHUNKSIZE + 1) * (CHUNKSIZE + 1) * (CHUNKSIZE + 1) * 3 * sizeof(short);
	chunks[center + x + y + z]->getVbo();

	return glm::vec3(0,0,0);
}

void World::render() const
{
	renderer->clear();
	for (unsigned char i = 0; i < vb.size(); ++i)
	{
		va->addBuffer(*(vb[i]), *layout);
		renderer->draw(*va, *(ib[i]), *shader);
	}
}

void World::update() const
{
	player->setFalling(false);
	if (player->getPos().y > 16.0f)
		player->setFalling(true);

	player->update((lastTime = glfwGetTime()) - worldTime);
	glm::mat4 pvm = glm::perspective(glm::radians(player->getFOV()), (float)player->getWinWidth() / (float)player->getWinHeight(), 0.1f, 100.0f);
	pvm *= player->getViewMatrix();
	shader->setUniformMat4f("u_PVM", pvm);
	worldTime = lastTime;
}

