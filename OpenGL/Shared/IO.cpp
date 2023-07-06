#include "pch.h"
#include "framework.h"

#include "IO.h"

// std
#include <iostream>
#include <fstream>

namespace shrd
{

	std::string read_file_into_string(const std::string& filename)
	{
		std::ifstream file(filename);

		std::string content{ std::istreambuf_iterator<char>(file),
							  std::istreambuf_iterator<char>() };

		file.close();

		return content;
	}

}
