#include "OpenGLVertexArray.h"

using namespace Honey;

#include <Honey/Core/Profiling.h>

extern "C" {
#include <glad/glad.h>
}

uint32_t OpenGLVertexArray::s_Bound = 0;

static GLenum ShaderToOpenGLDataType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:
		case ShaderDataType::Vector2:
		case ShaderDataType::Vector3:
		case ShaderDataType::Vector4:
		case ShaderDataType::Matrix3:
		case ShaderDataType::Matrix4:
			return GL_FLOAT;

		case ShaderDataType::Int:
		case ShaderDataType::Vector2Int:
		case ShaderDataType::Vector3Int:
		case ShaderDataType::Vector4Int:
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

	if (s_Bound == _rendererID) return;

	glBindVertexArray(_rendererID);
	s_Bound = _rendererID;
}

void OpenGLVertexArray::Unbind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound != _rendererID) return;

	glBindVertexArray(0);
	s_Bound = 0;
}

bool OpenGLVertexArray::IsBound() const
{
	return s_Bound == _rendererID;
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
		glEnableVertexAttribArray(_vertexBufferIndex);
		switch (e.Type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Vector2:
			case ShaderDataType::Vector3:
			case ShaderDataType::Vector4:
			case ShaderDataType::Bool:
			{
				glVertexAttribPointer(_vertexBufferIndex,
					e.GetComponentCount(),
					ShaderToOpenGLDataType(e.Type),
					e.IsNormalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)(uintptr_t)e.Offset);
				_vertexBufferIndex++;
				break;
			}

			case ShaderDataType::Int:
			case ShaderDataType::Vector2Int:
			case ShaderDataType::Vector3Int:
			case ShaderDataType::Vector4Int:
			{
				glVertexAttribIPointer(_vertexBufferIndex,
					e.GetComponentCount(),
					ShaderToOpenGLDataType(e.Type),
					layout.GetStride(),
					(const void*)(uintptr_t)e.Offset);
				_vertexBufferIndex++;
				break;
			}

			case ShaderDataType::Matrix3:
			case ShaderDataType::Matrix4:
			{
				uint8_t count = e.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glVertexAttribPointer(_vertexBufferIndex,
						count,
						ShaderToOpenGLDataType(e.Type),
						e.IsNormalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(uintptr_t)(e.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(_vertexBufferIndex, 1);
					_vertexBufferIndex++;
				}
				break;
			}

			default: HNY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		}
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
