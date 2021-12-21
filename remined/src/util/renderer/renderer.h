#ifndef RENDERER_H
#define RENDERER_H

#include "vertexArray.h"
#include "indexBuffer.h"
#include "util/shaders/shader.h"

class Renderer
{
private:

public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void clear() const;
	void enableBlend() const;
	void disableBlend() const;
};

#endif