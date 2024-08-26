#pragma once

#include "Ember/Core/Base.h"
#include "Ember/Renderer/Texture.h"

#include <filesystem>
#include <string_view>

namespace Ember
{

	class EMBER_API ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	
	private:
		std::filesystem::path m_CurrentDirectory;

		Ref<Texture2D> m_DirIcon;
		Ref<Texture2D> m_FileIcon;

	};

}
