#include "Emberpch.h"
#include "Ember/Core/Input.h"

#ifdef EMBER_PLATFORM_LINUX
    #include "Platform/Linux/LinuxInput.h"
#elif defined(EMBER_PLATFORM_WINDOWS)
    #include "Platform/Linux/LinuxInput.h" // This should be #include "Platform/Windows/WindowsInput.h"
#endif

namespace Ember
{
    Scope<Input> Input::s_instance = Input::Create();

    Scope<Input> Input::Create()
    {
        #ifdef EMBER_PLATFORM_LINUX
            return CreateScope<LinuxInput>();
        #elif defined(EMBER_PLATFORM_WINDOWS)
            return CreateScope<LinuxInput>(); // This should be return CreateScope<WindowsInput>();
        #else
            EMBER_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }
    
}