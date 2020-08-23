#include "OpenGLVertexArray.h"

using namespace Honey;

extern "C" {
#include <glad/glad.h>
}

static GLenum ShaderToOpenGLDataType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;

		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;

		case ShaderDataType::Bool:
			return GL_BOOL;
	}

	HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
	HNY_PROFILE_FUNCTION();

	glGenVertexArrays(1, &_rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	HNY_PROFILE_FUNCTION();

	glDeleteVertexArrays(1, &_rendererID);
}

void OpenGLVertexArray::Bind() const
{
	HNY_PROFILE_FUNCTION();

	glBindVertexArray(_rendererID);
}

void OpenGLVertexArray::Unbind() const
{
	HNY_PROFILE_FUNCTION();

	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const Reference<VertexBuffer>& buffer)
{
	HNY_PROFILE_FUNCTION();

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
			(const void*)(uintptr_t)e.Offset
		);

		index++;
	}

	_vertexBuffers.push_back(buffer);
}

void OpenGLVertexArray::SetIndexBuffer(const Reference<IndexBuffer>& buffer)
{
	HNY_PROFILE_FUNCTION();

	glBindVertexArray(_rendererID);
	buffer->Bind();

	_indexBuffer = buffer;
}
