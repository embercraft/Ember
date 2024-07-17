#pragma once

#include "Ember/Core/Base.h"

#include <optional>

namespace Ember
{

	class EMBER_API FileDialog
	{
	public:
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);

	};

}
