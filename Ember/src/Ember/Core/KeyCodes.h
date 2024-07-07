#pragma once

#include "Ember/Core/Core.h"

namespace Ember
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space			   = 32,
		Apostrophe		  = 39, /* ' */
		Comma			   = 44, /* , */
		Minus			   = 45, /* - */
		Period			  = 46, /* . */
		Slash			   = 47, /* / */

		D0				  = 48, /* 0 */
		D1				  = 49, /* 1 */
		D2				  = 50, /* 2 */
		D3				  = 51, /* 3 */
		D4				  = 52, /* 4 */
		D5				  = 53, /* 5 */
		D6				  = 54, /* 6 */
		D7				  = 55, /* 7 */
		D8				  = 56, /* 8 */
		D9				  = 57, /* 9 */

		Semicolon		   = 59, /* ; */
		Equal			   = 61, /* = */

		A				   = 65,
		B				   = 66,
		C				   = 67,
		D				   = 68,
		E				   = 69,
		F				   = 70,
		G				   = 71,
		H				   = 72,
		I				   = 73,
		J				   = 74,
		K				   = 75,
		L				   = 76,
		M				   = 77,
		N				   = 78,
		O				   = 79,
		P				   = 80,
		Q				   = 81,
		R				   = 82,
		S				   = 83,
		T				   = 84,
		U				   = 85,
		V				   = 86,
		W				   = 87,
		X				   = 88,
		Y				   = 89,
		Z				   = 90,

		LeftBracket		 = 91,  /* [ */
		Backslash		   = 92,  /* \ */
		RightBracket		= 93,  /* ] */
		GraveAccent		 = 96,  /* ` */

		World1			  = 161, /* non-US #1 */
		World2			  = 162, /* non-US #2 */

		/* Function keys */
		Escape			  = 256,
		Enter			   = 257,
		Tab				 = 258,
		Backspace		   = 259,
		Insert			  = 260,
		Delete			  = 261,
		Right			   = 262,
		Left				= 263,
		Down				= 264,
		Up				  = 265,
		PageUp			  = 266,
		PageDown			= 267,
		Home				= 268,
		End				 = 269,
		CapsLock			= 280,
		ScrollLock		  = 281,
		NumLock			 = 282,
		PrintScreen		 = 283,
		Pause			   = 284,
		F1				  = 290,
		F2				  = 291,
		F3				  = 292,
		F4				  = 293,
		F5				  = 294,
		F6				  = 295,
		F7				  = 296,
		F8				  = 297,
		F9				  = 298,
		F10				 = 299,
		F11				 = 300,
		F12				 = 301,
		F13				 = 302,
		F14				 = 303,
		F15				 = 304,
		F16				 = 305,
		F17				 = 306,
		F18				 = 307,
		F19				 = 308,
		F20				 = 309,
		F21				 = 310,
		F22				 = 311,
		F23				 = 312,
		F24				 = 313,
		F25				 = 314,

		/* Keypad */
		KP0				 = 320,
		KP1				 = 321,
		KP2				 = 322,
		KP3				 = 323,
		KP4				 = 324,
		KP5				 = 325,
		KP6				 = 326,
		KP7				 = 327,
		KP8				 = 328,
		KP9				 = 329,
		KPDecimal		   = 330,
		KPDivide			= 331,
		KPMultiply		  = 332,
		KPSubtract		  = 333,
		KPAdd			   = 334,
		KPEnter			 = 335,
		KPEqual			 = 336,

		LeftShift		   = 340,
		LeftControl		 = 341,
		LeftAlt			 = 342,
		LeftSuper		   = 343,
		RightShift		  = 344,
		RightControl		= 345,
		RightAlt			= 346,
		RightSuper		  = 347,
		Menu				= 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define EMBER_KEY_SPACE		   ::Ember::Key::Space
#define EMBER_KEY_APOSTROPHE	  ::Ember::Key::Apostrophe	/* ' */
#define EMBER_KEY_COMMA		   ::Ember::Key::Comma		 /* , */
#define EMBER_KEY_MINUS		   ::Ember::Key::Minus		 /* - */
#define EMBER_KEY_PERIOD		  ::Ember::Key::Period		/* . */
#define EMBER_KEY_SLASH		   ::Ember::Key::Slash		 /* / */
#define EMBER_KEY_0			   ::Ember::Key::D0
#define EMBER_KEY_1			   ::Ember::Key::D1
#define EMBER_KEY_2			   ::Ember::Key::D2
#define EMBER_KEY_3			   ::Ember::Key::D3
#define EMBER_KEY_4			   ::Ember::Key::D4
#define EMBER_KEY_5			   ::Ember::Key::D5
#define EMBER_KEY_6			   ::Ember::Key::D6
#define EMBER_KEY_7			   ::Ember::Key::D7
#define EMBER_KEY_8			   ::Ember::Key::D8
#define EMBER_KEY_9			   ::Ember::Key::D9
#define EMBER_KEY_SEMICOLON	   ::Ember::Key::Semicolon	 /* ; */
#define EMBER_KEY_EQUAL		   ::Ember::Key::Equal		 /* = */
#define EMBER_KEY_A			   ::Ember::Key::A
#define EMBER_KEY_B			   ::Ember::Key::B
#define EMBER_KEY_C			   ::Ember::Key::C
#define EMBER_KEY_D			   ::Ember::Key::D
#define EMBER_KEY_E			   ::Ember::Key::E
#define EMBER_KEY_F			   ::Ember::Key::F
#define EMBER_KEY_G			   ::Ember::Key::G
#define EMBER_KEY_H			   ::Ember::Key::H
#define EMBER_KEY_I			   ::Ember::Key::I
#define EMBER_KEY_J			   ::Ember::Key::J
#define EMBER_KEY_K			   ::Ember::Key::K
#define EMBER_KEY_L			   ::Ember::Key::L
#define EMBER_KEY_M			   ::Ember::Key::M
#define EMBER_KEY_N			   ::Ember::Key::N
#define EMBER_KEY_O			   ::Ember::Key::O
#define EMBER_KEY_P			   ::Ember::Key::P
#define EMBER_KEY_Q			   ::Ember::Key::Q
#define EMBER_KEY_R			   ::Ember::Key::R
#define EMBER_KEY_S			   ::Ember::Key::S
#define EMBER_KEY_T			   ::Ember::Key::T
#define EMBER_KEY_U			   ::Ember::Key::U
#define EMBER_KEY_V			   ::Ember::Key::V
#define EMBER_KEY_W			   ::Ember::Key::W
#define EMBER_KEY_X			   ::Ember::Key::X
#define EMBER_KEY_Y			   ::Ember::Key::Y
#define EMBER_KEY_Z			   ::Ember::Key::Z
#define EMBER_KEY_LEFT_BRACKET	::Ember::Key::LeftBracket   /* [ */
#define EMBER_KEY_BACKSLASH	   ::Ember::Key::Backslash	 /* \ */
#define EMBER_KEY_RIGHT_BRACKET   ::Ember::Key::RightBracket  /* ] */
#define EMBER_KEY_GRAVE_ACCENT	::Ember::Key::GraveAccent   /* ` */
#define EMBER_KEY_WORLD_1		 ::Ember::Key::World1		/* non-US #1 */
#define EMBER_KEY_WORLD_2		 ::Ember::Key::World2		/* non-US #2 */

/* Function keys */
#define EMBER_KEY_ESCAPE		  ::Ember::Key::Escape
#define EMBER_KEY_ENTER		   ::Ember::Key::Enter
#define EMBER_KEY_TAB			 ::Ember::Key::Tab
#define EMBER_KEY_BACKSPACE	   ::Ember::Key::Backspace
#define EMBER_KEY_INSERT		  ::Ember::Key::Insert
#define EMBER_KEY_DELETE		  ::Ember::Key::Delete
#define EMBER_KEY_RIGHT		   ::Ember::Key::Right
#define EMBER_KEY_LEFT			::Ember::Key::Left
#define EMBER_KEY_DOWN			::Ember::Key::Down
#define EMBER_KEY_UP			  ::Ember::Key::Up
#define EMBER_KEY_PAGE_UP		 ::Ember::Key::PageUp
#define EMBER_KEY_PAGE_DOWN	   ::Ember::Key::PageDown
#define EMBER_KEY_HOME			::Ember::Key::Home
#define EMBER_KEY_END			 ::Ember::Key::End
#define EMBER_KEY_CAPS_LOCK	   ::Ember::Key::CapsLock
#define EMBER_KEY_SCROLL_LOCK	 ::Ember::Key::ScrollLock
#define EMBER_KEY_NUM_LOCK		::Ember::Key::NumLock
#define EMBER_KEY_PRINT_SCREEN	::Ember::Key::PrintScreen
#define EMBER_KEY_PAUSE		   ::Ember::Key::Pause
#define EMBER_KEY_F1			  ::Ember::Key::F1
#define EMBER_KEY_F2			  ::Ember::Key::F2
#define EMBER_KEY_F3			  ::Ember::Key::F3
#define EMBER_KEY_F4			  ::Ember::Key::F4
#define EMBER_KEY_F5			  ::Ember::Key::F5
#define EMBER_KEY_F6			  ::Ember::Key::F6
#define EMBER_KEY_F7			  ::Ember::Key::F7
#define EMBER_KEY_F8			  ::Ember::Key::F8
#define EMBER_KEY_F9			  ::Ember::Key::F9
#define EMBER_KEY_F10			 ::Ember::Key::F10
#define EMBER_KEY_F11			 ::Ember::Key::F11
#define EMBER_KEY_F12			 ::Ember::Key::F12
#define EMBER_KEY_F13			 ::Ember::Key::F13
#define EMBER_KEY_F14			 ::Ember::Key::F14
#define EMBER_KEY_F15			 ::Ember::Key::F15
#define EMBER_KEY_F16			 ::Ember::Key::F16
#define EMBER_KEY_F17			 ::Ember::Key::F17
#define EMBER_KEY_F18			 ::Ember::Key::F18
#define EMBER_KEY_F19			 ::Ember::Key::F19
#define EMBER_KEY_F20			 ::Ember::Key::F20
#define EMBER_KEY_F21			 ::Ember::Key::F21
#define EMBER_KEY_F22			 ::Ember::Key::F22
#define EMBER_KEY_F23			 ::Ember::Key::F23
#define EMBER_KEY_F24			 ::Ember::Key::F24
#define EMBER_KEY_F25			 ::Ember::Key::F25

/* Keypad */
#define EMBER_KEY_KP_0			::Ember::Key::KP0
#define EMBER_KEY_KP_1			::Ember::Key::KP1
#define EMBER_KEY_KP_2			::Ember::Key::KP2
#define EMBER_KEY_KP_3			::Ember::Key::KP3
#define EMBER_KEY_KP_4			::Ember::Key::KP4
#define EMBER_KEY_KP_5			::Ember::Key::KP5
#define EMBER_KEY_KP_6			::Ember::Key::KP6
#define EMBER_KEY_KP_7			::Ember::Key::KP7
#define EMBER_KEY_KP_8			::Ember::Key::KP8
#define EMBER_KEY_KP_9			::Ember::Key::KP9
#define EMBER_KEY_KP_DECIMAL	  ::Ember::Key::KPDecimal
#define EMBER_KEY_KP_DIVIDE	   ::Ember::Key::KPDivide
#define EMBER_KEY_KP_MULTIPLY	 ::Ember::Key::KPMultiply
#define EMBER_KEY_KP_SUBTRACT	 ::Ember::Key::KPSubtract
#define EMBER_KEY_KP_ADD		  ::Ember::Key::KPAdd
#define EMBER_KEY_KP_ENTER		::Ember::Key::KPEnter
#define EMBER_KEY_KP_EQUAL		::Ember::Key::KPEqual

#define EMBER_KEY_LEFT_SHIFT	  ::Ember::Key::LeftShift
#define EMBER_KEY_LEFT_CONTROL	::Ember::Key::LeftControl
#define EMBER_KEY_LEFT_ALT		::Ember::Key::LeftAlt
#define EMBER_KEY_LEFT_SUPER	  ::Ember::Key::LeftSuper
#define EMBER_KEY_RIGHT_SHIFT	 ::Ember::Key::RightShift
#define EMBER_KEY_RIGHT_CONTROL   ::Ember::Key::RightControl
#define EMBER_KEY_RIGHT_ALT	   ::Ember::Key::RightAlt
#define EMBER_KEY_RIGHT_SUPER	 ::Ember::Key::RightSuper
#define EMBER_KEY_MENU			::Ember::Key::Menu
