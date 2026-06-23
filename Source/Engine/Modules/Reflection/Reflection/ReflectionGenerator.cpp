#include "Lexer.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include "ReflectionGenerator.h"

void ReflectionGenerator::Generate(const std::unordered_map<std::string, Class>& classes) const
{
	for (auto& [name, cls] : classes)
	{
		GenerateReflectionClass(name, cls);
	}
}

void ReflectionGenerator::GenerateReflectionClass(const std::string& name, const Class& cls) const
{
	std::cout << "Generating: " << name << std::endl;

	const std::string generatedFilepath = name + ".generated.cpp";

	std::stringstream stream;

	if (!cls._namespace.empty())
	{
		stream << "using namespace " << cls._namespace << ";"  "\n\n";
	}

	stream << "#include \"" << cls.filepath << "\"\n";
	stream << "#include \"" << (std::filesystem::path(__FILE__).parent_path() / "ReflectionCommon.hpp").generic_string() << "\"\n";

	stream << "\n";

	stream << "BASE(" << name << ");\n";
	stream << "TYPE_INFO_STRUCT\n";
	stream << "{\n";
	stream << "	NAME(" << name << ");\n\n";

	for (const VariableInfo& var : cls.variables)
	{
		stream << "	PROPERTY(" << var.name << ");\n";
	}

	stream << "\n";

	stream << "	PROPERTY_LIST(\n";
	for (size_t i = 0; i < cls.variables.size(); i++)
	{
		const VariableInfo& var = cls.variables[i];
		stream << "		&" << var.name;

		if (i != cls.variables.size() - 1)
			stream << ",";

		stream << "\n";
	}
	stream << "	);\n\n";

	stream << "	PROPERTY_COUNT(" << cls.variables.size() <<  ");\n";
	stream << "	GETTER_METHODS;\n";
	stream << "};\n\n";
	stream << "REGISTRATOR;\n";

	std::ofstream out(name + ".generated.cpp");
	out << stream.str();
}