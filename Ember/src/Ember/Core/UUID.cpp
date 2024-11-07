#include "Emberpch.h"
#include "Ember/Core/UUID.h"

#include <random>

namespace Ember
{

	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Generator(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	UUID::UUID()
		: m_UUID(s_UniformDistribution(s_Generator))
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}
}