#pragma once

#include "Ember/Core/Base.h"

#include <glm/glm.hpp>

namespace Ember
{

	class EMBER_API Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projectionMatrix)
			: m_ProjectionMatrix(projectionMatrix) {}
		
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
	
	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4{ 1.0f };
	};

}