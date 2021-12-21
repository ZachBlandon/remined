#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned char* data, unsigned int count);
	IndexBuffer(const unsigned short* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	inline unsigned int getCount() const { return m_count; }
};

#endif