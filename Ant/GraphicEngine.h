#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <istream>
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
	TTF_Font *font;
	SDL_Color colorFont;
	SDL_Surface * surfaceText;
	SDL_Texture* text;
	std::mutex mtx;

	void DrawWindow();
	void DrawCustomText();
public:
	GraphicEngine(Core *);
	~GraphicEngine();

	float offsettime;
	bool isRunning;
	bool isPaused;
	bool justRefreshed;

	void RefreshWindow();
	void DrawOneTime();
	bool Init();
	void Update();
};

