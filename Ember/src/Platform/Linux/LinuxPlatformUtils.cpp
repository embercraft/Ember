#include "Emberpch.h"
#include "Ember/Utils/PlatformUtils.h"

#include <cstdlib>
#include <memory>
#include <array>
#include <optional>
#include <unistd.h>

namespace Ember
{

	static std::optional<std::string> ExecuteZenityCommand(const std::string& command)
	{
		std::array<char, 128> buffer;
		std::string result;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

		if (!pipe) {
			EMBER_ASSERT(false, "popen() failed!");
			return std::nullopt;
		}

		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			result += buffer.data();
		}

		// Remove trailing newline
		if (!result.empty() && result[result.length() - 1] == '\n') {
			result.erase(result.length() - 1);
		}

		// If the result is empty, it means no file was selected
		if (result.empty()) {
			return std::nullopt;
		}

		return result;
	}

	std::optional<std::string> FileDialog::OpenFile(const char* filter)
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) == nullptr) {
			EMBER_ASSERT(false, "getcwd() failed!");
			return std::nullopt;
		}

		std::string command = "zenity --file-selection --title='Open File' ";
		command += "--file-filter='";
		command += filter;
		command += "' --file-filter='All files | *' ";
		command += "--filename='";
		command += cwd;
		command += "/'";

		return ExecuteZenityCommand(command);
	}

	std::optional<std::string> FileDialog::SaveFile(const char* filter)
	{
		std::string command = "zenity --file-selection --save --confirm-overwrite --title='Save File' ";
		command += "--file-filter='";
		command += filter;
		command += "' --file-filter='All files | *' ";
		command += "--filename='Untitled.ember'";

		return ExecuteZenityCommand(command);
	}

}
