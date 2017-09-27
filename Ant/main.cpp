#include "Core.h"
#include "GraphicEngine.h"
#include "ConsoleParsing.h"

#include <windows.h>
#include <string>
#include <iostream>
int main(int argc, char **argv)
{
	Core core;
	GraphicEngine graph(&core);
	ConsoleParsing consolePars(&core, &graph);

	if (!core.Init())
		return EXIT_FAILURE;
	if (!graph.Init())
		return EXIT_FAILURE;
	std::thread graphThread(&GraphicEngine::Update, &graph);
	std::thread coreThread(&Core::Update, &core);

	consolePars.Update();
	graphThread.join();
	coreThread.join();
	return EXIT_SUCCESS;
}