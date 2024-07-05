#pragma once

#include "Ember/Core/Core.h"

#include "Ember/Renderer/OrthographicCamera.h"

#include "Ember/Core/Timestep.h"

#include "Ember/Events/ApplicationEvent.h"
#include "Ember/Events/MouseEvent.h"

#include "Ember/Core/KeyCodes.h"

#include <glm/glm.hpp>

namespace Ember {

    class EMBER_API OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        inline OrthographicCamera& GetCamera() { return m_Camera; }
        inline const OrthographicCamera& GetCamera() const { return m_Camera; }

        inline float GetZoomLevel() { return m_ZoomLevel; }
        inline void SetZoomLevel(float level) { m_ZoomLevel = level; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
        bool m_Rotation = false;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;

        float m_CameraTranslationSpeed = 5.0f;
        float m_CameraRotationSpeed = 180.0f;
    };

}
