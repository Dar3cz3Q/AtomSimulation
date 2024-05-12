#pragma once

#include <vector>
#include "glad/glad.h"
#include "Renderer.h"
#include "Vertex.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized) : type(type), count(count), normalized(normalized) {};

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_Stride(0) {};

	template<typename T>
	void Push(unsigned int count) = delete;

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back(VertexBufferElement( GL_FLOAT, count, GL_FALSE ));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back(VertexBufferElement( GL_UNSIGNED_INT, count, GL_FALSE));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back(VertexBufferElement( GL_UNSIGNED_BYTE, count, GL_TRUE ));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline unsigned int GetStride() const { return m_Stride; };
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};

