#include <ctime>
#include <iostream>
#include <istream>

#include "GraphicEngine.h"
#include "Core.h"

void InitAnt(Core* core)
{
	core->winwowWidth = 900;
	core->winwowHeigth = 900;
	core->caseTerrainWidth = 10;
	core->caseTerrainHeigth = 10;
	core->terrainWidth = 10;
	core->terrainHeigth = 10;
	core->zoom = 1;
}

int main(int argc, char **argv)
{
	Core core;
	GraphicEngine* graph = new GraphicEngine(&core);
	InitAnt(&core);

	time_t start = time(0);
	start += 5;

	graph->Init();
	core.Init();

	std::thread first(&GraphicEngine::Update, graph);

	int answer;
	//std::cin >> answer;
	clock_t begin_time = clock();
	int flag = 0;
	while (42)
	{
		flag++;
		if (flag == 100)
		{
			core.Update();
			flag = 0;
		}
	}
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