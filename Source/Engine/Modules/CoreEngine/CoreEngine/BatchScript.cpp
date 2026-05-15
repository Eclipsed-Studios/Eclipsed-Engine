#include "BatchScript.h"

namespace Eclipse
{
	BatchScript::BatchScript(const std::filesystem::path& aWorkingDir, const std::string& aCommand, const std::vector<std::string>& args)
		: workingDir(aWorkingDir), command(aCommand), arguments(args)
	{

	}

	BatchScript::BatchScript(const std::filesystem::path& aWorkingDir, const std::string& aCommand)
		: workingDir(aWorkingDir), command(aCommand)
	{

	}

	void BatchScript::SetWorkingDirectory(const std::filesystem::path& aWorkingDir)
	{
		workingDir = aWorkingDir;
	}

	void BatchScript::SetCommand(const std::string& aCommand)
	{
		command = aCommand;
	}

	void BatchScript::AddArgument(const std::string& arg)
	{
		arguments.push_back(arg);
	}

	void BatchScript::SetArguments(const std::vector<std::string>& args)
	{
		arguments = args;
	}

	void BatchScript::ClearArguments()
	{
		arguments.clear();
	}

	bool BatchScript::Run(bool openNewWindow) const
	{
		return system(BuildCommandString(openNewWindow).c_str()) == 0;
	}

	std::string BatchScript::BuildCommandString(bool openNewWindow) const
	{
		std::string cmd = "cd /d \"" + workingDir.generic_string() + "\" && ";

		if (openNewWindow)
			cmd += "start ";

		cmd += command;

		for (const std::string& arg : arguments)
			cmd += " " + arg;

		return cmd;
	}
}