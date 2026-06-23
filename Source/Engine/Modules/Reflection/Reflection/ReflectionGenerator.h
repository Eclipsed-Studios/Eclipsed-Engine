#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Data.h"

class ReflectionGenerator
{
public:
	void Generate(const std::unordered_map<std::string, Class>& classes) const;

private:
	void GenerateReflectionClass(const std::string& name, const Class& cls) const;
};