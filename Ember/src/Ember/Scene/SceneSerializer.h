#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Scene/Scene.h"

namespace Ember
{

	class EMBER_API SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);

	private:
		Ref<Scene> m_Scene;

	};

}