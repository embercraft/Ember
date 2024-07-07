#include "Emberpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Ember{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Ember::ShaderDataType::Float:	return GL_FLOAT;
			case Ember::ShaderDataType::Float2:   return GL_FLOAT;
			case Ember::ShaderDataType::Float3:   return GL_FLOAT;
			case Ember::ShaderDataType::Float4:   return GL_FLOAT;
			case Ember::ShaderDataType::Mat3:	 return GL_FLOAT;
			case Ember::ShaderDataType::Mat4:	 return GL_FLOAT;
			case Ember::ShaderDataType::Int:	  return GL_INT;
			case Ember::ShaderDataType::Int2:	 return GL_INT;
			case Ember::ShaderDataType::Int3:	 return GL_INT;
			case Ember::ShaderDataType::Int4:	 return GL_INT;
			case Ember::ShaderDataType::Bool:	 return GL_BOOL;
		}

		EMBER_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		EMBER_PROFILE_FUNCTION();
		
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		EMBER_PROFILE_FUNCTION();
		
		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	void OpenGLVertexArray::Bind() const
	{
		EMBER_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		EMBER_PROFILE_FUNCTION();
		
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		EMBER_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		EMBER_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
