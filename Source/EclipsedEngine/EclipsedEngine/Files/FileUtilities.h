#pragma once

#include <string>
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Files
{
	std::string ECL_API SelectFolderDialog();
	std::string ECL_API SelectFileDialog();
	std::string ECL_API SaveFileDialog();
}