#pragma once
#include "glad/glad.h"
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void LinkAttribute(const VertexBuffer& vb, unsigned int location, unsigned int count, GLenum type, size_t size);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
	unsigned int m_Offset;
};