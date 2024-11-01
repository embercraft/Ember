#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Core/Log.h"
#include "Ember/Scene/Scene.h"
#include "Ember/Scene/Entity.h"
#include "Ember/Scene/Components.h"

namespace Ember
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);
		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();

		void SetSelectedEntity( Entity entity);
		Entity GetSelectedEntity() const { return m_SelectionContext; }

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}