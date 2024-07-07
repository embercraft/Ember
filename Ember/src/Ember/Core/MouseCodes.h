#pragma once

#include <cstdint>
#include <iostream>

namespace Ember
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

namespace fmt
{
    template <>
    struct formatter<Ember::MouseCode> : formatter<int32_t>
    {
        template <typename FormatContext>
        auto format(Ember::MouseCode mouseCode, FormatContext& ctx)
        {
            return formatter<int32_t>::format(static_cast<int32_t>(mouseCode), ctx);
        }
    };
}

#define EMBER_MOUSE_BUTTON_0      ::Ember::Mouse::Button0
#define EMBER_MOUSE_BUTTON_1      ::Ember::Mouse::Button1
#define EMBER_MOUSE_BUTTON_2      ::Ember::Mouse::Button2
#define EMBER_MOUSE_BUTTON_3      ::Ember::Mouse::Button3
#define EMBER_MOUSE_BUTTON_4      ::Ember::Mouse::Button4
#define EMBER_MOUSE_BUTTON_5      ::Ember::Mouse::Button5
#define EMBER_MOUSE_BUTTON_6      ::Ember::Mouse::Button6
#define EMBER_MOUSE_BUTTON_7      ::Ember::Mouse::Button7
#define EMBER_MOUSE_BUTTON_LAST   ::Ember::Mouse::ButtonLast
#define EMBER_MOUSE_BUTTON_LEFT   ::Ember::Mouse::ButtonLeft
#define EMBER_MOUSE_BUTTON_RIGHT  ::Ember::Mouse::ButtonRight
#define EMBER_MOUSE_BUTTON_MIDDLE ::Ember::Mouse::ButtonMiddle