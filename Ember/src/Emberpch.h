#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <assert.h>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Ember/Core/Log.h"

#ifdef EMBER_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#ifdef EMBER_PLATFORM_LINUX
	#include <unistd.h>		 // Provides access to the POSIX operating system API
	#include <sys/types.h>   // Defines data types used in system calls
	#include <sys/stat.h>	 // Defines the structure of the data returned by the functions fstat(), lstat(), and stat()
	#include <fcntl.h>		 // File control options
	#include <dlfcn.h>		 // Dynamic linking
	#include <signal.h>		 // Signal handling
	#include <errno.h>		 // Error handling
	#include <cstring>		 // C string handling functions
	#include <cstdlib>		 // Standard library functions
	#include <ctime>		 // Time functions
	#include <sys/time.h>	 // Higher resolution time functions
#endif
