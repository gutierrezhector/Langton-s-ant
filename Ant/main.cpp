#include <ctime>
#include <iostream>

#include "GraphicEngine.h"
#include "Core.h"
#include "ConsoleParsing.h"


int main(int argc, char **argv)
{
	Core core;
	GraphicEngine graph(&core);
	ConsoleParsing consolePars(&core, &graph);
	
	core.Init();
	graph.Init();

	std::thread graphThread(&GraphicEngine::Update, &graph);
	std::thread coreThread(&Core::Update, &core);

	consolePars.Update();
	graphThread.join();
	coreThread.join();
	return EXIT_SUCCESS;
}

/*
while (42)
{
if (begin_time < clock())
{
core.Update();
begin_time = clock();
}
}
*/