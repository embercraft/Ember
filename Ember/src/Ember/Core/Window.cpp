#include "Emberpch.h"
#include "Ember/Core/Window.h"

#ifdef EMBER_PLATFORM_LINUX
    #include "Platform/Linux/LinuxWindow.h"
#elif defined(EMBER_PLATFORM_WINDOWS)
    #include "Platform/Linux/LinuxWindow.h" // This should be  #include "Platform/Windows/WindowsWindow.h"
#endif

namespace Ember
{

    Scope<Window> Window::Create(const WindowProps& props)
    {
        #ifdef EMBER_PLATFORM_LINUX
            return CreateScope<LinuxWindow>(props);
        #elif defined(EMBER_PLATFORM_WINDOWS)
            return CreateScope<LinuxWindow>(props); // This should be return CreateScope<WindowsWindow>(props);
        #else
            EMBER_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }

}
