#include "Emberpch.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Ember
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        // Color attachment
        glGenTextures(1, &m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        // Depth attachment
        glGenTextures(1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status == GL_FRAMEBUFFER_COMPLETE) {
			EMBER_CORE_INFO("Framebuffer complete.");
		} else {
			std::string error = "Framebuffer is incomplete. Status: ";
			switch(status)
			{
				case GL_FRAMEBUFFER_UNDEFINED: error += "GL_FRAMEBUFFER_UNDEFINED"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: error += "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: error += "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: error += "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: error += "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
				case GL_FRAMEBUFFER_UNSUPPORTED: error += "GL_FRAMEBUFFER_UNSUPPORTED"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: error += "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: error += "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
				default: error += "Unknown error";
			}
			EMBER_CORE_CRITICAL("{0}", error);
		}

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}
}