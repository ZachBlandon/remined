#ifndef WORLD_H
#define WORLD_H

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "util/renderer/renderer.h"
#include "util/shaders/shader.h"
#include "util/shaders/texture.h"
#include "player/player.h"
#include "chunk.h"

class World
{
private:
	static double worldTime;
	static double lastTime;
	Shader* shader;
	Texture* texture;
	Player* player;
	Renderer* renderer;
	VertexArray* va;
	VertexBufferLayout* layout;
	std::vector<Chunk*> chunks;
	std::vector<VertexBuffer*> vb;
	std::vector<IndexBuffer*> ib;

	World(Player* player);
	void generateChunks();

public:
	static World* getInstance(Player* player);
	glm::vec3 getWorldPos(glm::vec3 playerPos);
	void render() const;
	void update() const;
};

#endif