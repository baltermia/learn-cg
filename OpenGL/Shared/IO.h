#pragma once

// std
#include <string_view>

namespace shrd
{
	bool file_exists(std::string_view filename);

	std::string read_file_into_string(std::string_view filename);
}