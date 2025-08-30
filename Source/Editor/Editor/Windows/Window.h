#pragma once
#include <string>

class AbstractWindow {
	friend class Editor;

public:
	virtual void Open() = 0;
	virtual void Update() = 0;
	virtual void Close() = 0;

public:
	const int& GetID();
	const int& GetID() const;

	const std::string& GetWindowName();
	const std::string& GetWindowName() const;

protected:
	std::string myWindowName;
	int myID;
	bool myIsOpen = true;

	bool myWasLastOpen = true;
};