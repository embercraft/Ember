#pragma once

#include "Ember/Core/Base.h"

#include <glm/glm.hpp>

namespace Ember::Math
{
	
	bool DecomposeTransform(const glm::mat4& inTransform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale);

}
