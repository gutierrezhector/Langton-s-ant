#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>

#include "Struct.h"
#include "Core.h"

class Core;
class GraphicEngine
{
private:
	SDL_Window * mainWindow;
	SDL_Renderer * renderer;
	Core * coreInstance;
	time_t saveTime;
public:
	GraphicEngine(Core *);
	~GraphicEngine();

	float offsettime;
	bool isRunning;

	int Init();
	bool Update();
};

