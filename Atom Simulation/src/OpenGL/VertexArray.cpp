#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
	: m_Offset(0)
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) 
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	vb.Unbind();
}

void VertexArray::LinkAttribute(const VertexBuffer& vb, unsigned int location, unsigned int count, GLenum type, size_t size)
{
	Bind();
	vb.Bind();

	glVertexAttribPointer(location, count, type, GL_FALSE, static_cast<GLsizei>(size), (const void*)m_Offset);
	glEnableVertexAttribArray(location);

	m_Offset += count * VertexBufferElement::GetSizeOfType(type);

	vb.Unbind();
}

void VertexArray::LinkAttribute(const VertexBuffer& vb, unsigned int location, unsigned int count, GLenum type, size_t size, size_t stride)
{
	Bind();
	vb.Bind();

	glVertexAttribPointer(location, count, type, GL_FALSE, static_cast<GLsizei>(size), (const void*)(stride * VertexBufferElement::GetSizeOfType(type)));
	glEnableVertexAttribArray(location);

	vb.Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
