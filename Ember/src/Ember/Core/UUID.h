#pragma once

#include "Ember/Core/Base.h"

#include <functional>

namespace Ember
{
	class EMBER_API UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID& other) = default;

		operator uint64_t() const { return m_UUID; }

	private:
		uint64_t m_UUID;
	};
}

namespace std
{
	template<>
	struct hash<Ember::UUID>
	{
		size_t operator()(const Ember::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}
