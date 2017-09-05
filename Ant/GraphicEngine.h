#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <mutex>

#include "Struct.h"
#include "Core.h"

class Core;
class GraphicEngine
{
private:
	SDL_Window * mainWindow;
	SDL_Renderer * renderer;
	Core * coreInstance;
	std::mutex mtx;
public:
	GraphicEngine(Core *);
	~GraphicEngine();

	float offsettime;
	bool isRunning;
	bool isPaused;
	bool justRefreshed;

	void RefreshWindow();
	bool Init();
	void Update();
};

