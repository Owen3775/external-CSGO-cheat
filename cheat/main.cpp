#include "gui.h"
#include "globals.h"
#include "misc.h"
#include <thread>
#include "visuals.h"
#include "aimbot.h"
#include <iostream>
#include <cstddef> 
#include <cstdint>


int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{	
	BOOL WINAPI AllocConsole();
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	std::cout << "successful opening" << std::endl;
	Sleep(1000);
	fclose(fDummy);
	BOOL WINAPI FreeConsole();
	FreeConsole();

	Memory mem{ "csgo.exe" };
	globals::bClient = mem.GetModuleAddress("client.dll");
	globals::bEngine = mem.GetModuleAddress("engine.dll");


	std::thread(visuals::visualThread, mem).detach();
	std::thread(misc::miscThread, mem).detach();
	std::thread(aimbot::aimbotThread, mem).detach();
	std::thread(visuals::chamsThread, mem).detach();

	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::exit)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyWindow();

	return EXIT_SUCCESS;
}

int main()
{
}

