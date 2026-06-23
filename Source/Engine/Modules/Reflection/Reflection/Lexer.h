#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Data.h"

class Lexer
{
public:
	void Tokenize(const char* filepath);

	const std::unordered_map<std::string, Class>& GetClasses() const;

private:
	std::vector<MethodInfo> ParseMethodDeclarations(const char* classSource);
	std::vector<VariableInfo> ParseVariableDeclarations(const char* classSource);

private:
	std::unordered_map<std::string, Class> classes;
};