#include "OpenGLVertexArray.h"

using namespace Honey;

#include <glad/glad.h>

static GLenum ShaderToOpenGLDataType(ShaderDataType type)
{
	switch (type)
	{
		case Honey::ShaderDataType::Float:
		case Honey::ShaderDataType::Float2:
		case Honey::ShaderDataType::Float3:
		case Honey::ShaderDataType::Float4:
		case Honey::ShaderDataType::Mat3:
		case Honey::ShaderDataType::Mat4:
			return GL_FLOAT;

		case Honey::ShaderDataType::Int:
		case Honey::ShaderDataType::Int2:
		case Honey::ShaderDataType::Int3:
		case Honey::ShaderDataType::Int4:
			return GL_INT;

		case Honey::ShaderDataType::Bool:
			return GL_BOOL;
	}

	HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
	glGenBuffers(1, &_rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteBuffers(1, &_rendererID);
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(_rendererID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
{
	HNY_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "Layout not set on Vertex Buffer!");

	glBindVertexArray(_rendererID);
	buffer->Bind();

	uint32_t index = 0;
	const BufferLayout& layout = buffer->GetLayout();
	for (const BufferElement& e : layout)
	{
		glEnableVertexAttribArray(index);

		glVertexAttribPointer
		(
			index,
			e.GetComponentCount(),
			ShaderToOpenGLDataType(e.Type),
			e.IsNormalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)e.Offset
		);

		index++;
	}

	_vertexBuffers.push_back(buffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
{
	glBindVertexArray(_rendererID);
	buffer->Bind();

	_indexBuffer = buffer;
}