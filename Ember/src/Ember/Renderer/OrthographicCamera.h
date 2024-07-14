#pragma once

#include "Ember/Core/Base.h"

#include <glm/glm.hpp>

namespace Ember {

	class EMBER_API OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		
		void SetProjection(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void setPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		inline float GetRotation() const { return m_Rotation; }
		inline void setRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}
