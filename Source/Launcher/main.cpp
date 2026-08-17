
#include "EclipsedEngine/Core/EclipsedEngine.h"
#include <iostream>
#include <Windows.h>

//int main(int argc, char* argv[])
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Eclipse::Engine t;
	t.Test();

	while (!t.ShouldClose())
	{
		t.BeginFrame();
		t.Render();
		t.EndFrame();
	}
}