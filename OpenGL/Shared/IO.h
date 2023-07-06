#pragma once

// std
#include <string>

namespace shrd
{
	bool file_exists(const std::string& filename);

	std::string read_file_into_string(const std::string& filename);
}