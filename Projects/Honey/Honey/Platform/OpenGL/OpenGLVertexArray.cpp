#include "OpenGLVertexArray.h"

using namespace Honey;

#include <Honey/Core/Profiling.h>

extern "C" {
#include <glad/glad.h>
}

UInt OpenGLVertexArray::s_Bound = 0;

static GLenum shaderDataTypeToOpenGL(ShaderDataType type)
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

	glCreateVertexArrays(1, &_rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	HNY_PROFILE_FUNCTION();

	glDeleteVertexArrays(1, &_rendererID);
}

void OpenGLVertexArray::bind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound == _rendererID) return;

	glBindVertexArray(_rendererID);
	s_Bound = _rendererID;
}

void OpenGLVertexArray::unbind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound != _rendererID) return;

	glBindVertexArray(0);
	s_Bound = 0;
}

bool OpenGLVertexArray::isBound() const
{
	return s_Bound == _rendererID;
}

void OpenGLVertexArray::addVertexBuffer(const Reference<VertexBuffer>& buffer)
{
	HNY_PROFILE_FUNCTION();

	HNY_CORE_ASSERT(buffer->getLayout().getElements().size(), "Layout not set on Vertex Buffer!");

	bind();
	buffer->bind();

	UInt index = 0;
	const BufferLayout& layout = buffer->getLayout();
	for (const BufferElement& e : layout)
	{
		glEnableVertexAttribArray(_vertexBufferIndex);
		switch (e.type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Vector2:
			case ShaderDataType::Vector3:
			case ShaderDataType::Vector4:
			case ShaderDataType::Bool:
			{
				glVertexAttribPointer(_vertexBufferIndex,
					e.getComponentCount(),
					shaderDataTypeToOpenGL(e.type),
					e.isNormalized ? GL_TRUE : GL_FALSE,
					layout.getStride(),
					(const void*)(uintptr_t)e.offset);
				_vertexBufferIndex++;
				break;
			}

			case ShaderDataType::Int:
			case ShaderDataType::Vector2Int:
			case ShaderDataType::Vector3Int:
			case ShaderDataType::Vector4Int:
			{
				glVertexAttribIPointer(_vertexBufferIndex,
					e.getComponentCount(),
					shaderDataTypeToOpenGL(e.type),
					layout.getStride(),
					(const void*)(uintptr_t)e.offset);
				_vertexBufferIndex++;
				break;
			}

			case ShaderDataType::Matrix3:
			case ShaderDataType::Matrix4:
			{
				Byte count = e.getComponentCount();
				for (Byte i = 0; i < count; i++)
				{
					glVertexAttribPointer(_vertexBufferIndex,
						count,
						shaderDataTypeToOpenGL(e.type),
						e.isNormalized ? GL_TRUE : GL_FALSE,
						layout.getStride(),
						(const void*)(uintptr_t)(e.offset + sizeof(Float) * count * i));
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

void OpenGLVertexArray::setIndexBuffer(const Reference<IndexBuffer>& buffer)
{
	HNY_PROFILE_FUNCTION();

	bind();
	buffer->bind();
	_indexBuffer = buffer;
}
