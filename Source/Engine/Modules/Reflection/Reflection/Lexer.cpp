#include "Lexer.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

void Lexer::Tokenize(const char* filepath)
{
	std::ifstream file(filepath);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filepath << '\n';
		return;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string source = buffer.str();

	std::regex pattern(
		R"(CLS\s+((?:namespace\s+([a-zA-Z_][a-zA-Z0-9_:]*)\s*\{)?\s*class\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(?::\s*([^{]+))?\s*\{([\s\S]*?)\}\s*;?\s*(?:\})?)\s*END_CLS)"
	);

	std::sregex_iterator begin(source.begin(), source.end(), pattern);
	std::sregex_iterator end;

	for (auto it = begin; it != end; ++it)
	{
		const std::smatch& match = *it;
		std::string classSource = match[1].str();

		Class& cls = classes[match[3].str()] = {};
		cls._namespace = match[2].str();

		const std::vector<VariableInfo> variables = ParseVariableDeclarations(classSource.c_str());
		cls.variables.insert(cls.variables.begin(), variables.begin(), variables.end());

		const std::vector<MethodInfo> methods = ParseMethodDeclarations(classSource.c_str());
		cls.methods.insert(cls.methods.begin(), methods.begin(), methods.end());

		cls.filename = std::filesystem::path(filepath).filename().stem().string();
		cls.filepath = filepath;
	}
}

std::vector<MethodInfo> Lexer::ParseMethodDeclarations(const char* classSource)
{
	std::vector<MethodInfo> methods;

	const std::string source = classSource;

	std::regex methodPattern(R"(\[\[(.*?)\]\]\s*([a-zA-Z_][a-zA-Z0-9_:<>*]*)\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*\(\))");
	std::sregex_iterator beg(source.begin(), source.end(), methodPattern);
	std::sregex_iterator end;

	for (auto it = beg; it != end; ++it)
	{
		const std::smatch& varMatch = *it;
		methods.emplace_back(
			varMatch[1].str(),
			varMatch[2].str(),
			varMatch[3].str()
		);
	}

	return methods;
}

std::vector<VariableInfo> Lexer::ParseVariableDeclarations(const char* classSource)
{
	std::vector<VariableInfo> variables;

	const std::string source = classSource;

	std::regex variablePattern(R"(\[\[(.*?)\]\]\s*([a-zA-Z_][a-zA-Z0-9_:<>*&]*)\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*(?:[;=]|$))");
	std::sregex_iterator clsBeg(source.begin(), source.end(), variablePattern);
	std::sregex_iterator clsEnd;

	for (auto clsIt = clsBeg; clsIt != clsEnd; ++clsIt)
	{
		const std::smatch& varMatch = *clsIt;
		variables.emplace_back(
			varMatch[1].str(),
			varMatch[2].str(),
			varMatch[3].str()
		);
	}

	return variables;
}

const std::unordered_map<std::string, Class>& Lexer::GetClasses() const
{
	return classes;
}