#pragma once

struct VariableInfo
{
	std::string attributes;
	std::string type;
	std::string name;
};

struct MethodInfo
{
	std::string attributes;
	std::string returnType;
	std::string name;
};

struct Class
{
	std::string _namespace;
	std::string filepath;
	std::string filename;
	std::vector<MethodInfo> methods;
	std::vector<VariableInfo> variables;
};