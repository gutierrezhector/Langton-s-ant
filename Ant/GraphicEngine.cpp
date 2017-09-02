#include <windows.h>

#include "GraphicEngine.h"

GraphicEngine::GraphicEngine(Core* newCore)
{
	coreInstance = newCore;
	offsettime = 0;
	isRunning = true;
}


GraphicEngine::~GraphicEngine()
{
}

int GraphicEngine::Init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}
	mainWindow = SDL_CreateWindow("Anty", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, coreInstance->winwowWidth, coreInstance->winwowHeigth, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(mainWindow, -1, 0);
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 1);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Rect rect = {
		(coreInstance->winwowHeigth / 2) - ((coreInstance->terrainHeigth * coreInstance->caseTerrainHeigth * coreInstance->zoom) / 2),
		(coreInstance->winwowWidth / 2) - ((coreInstance->terrainWidth * coreInstance->caseTerrainWidth * coreInstance->zoom) / 2),
		coreInstance->caseTerrainWidth * coreInstance->terrainWidth * coreInstance->zoom,
		coreInstance->caseTerrainHeigth * coreInstance->terrainHeigth * coreInstance->zoom
	};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	saveTime = time(0) + 1;
	return EXIT_SUCCESS;
}

bool GraphicEngine::Update()
{
	while (isRunning)
	{
		for (int y = 0; y < coreInstance->terrainHeigth; y++)
		{
			for (int x = 0; x < coreInstance->terrainWidth; x++)
			{
				if (coreInstance->arrayGame[y][x].justChanged)
				{
					SDL_Rect rect = {
					(y * coreInstance->caseTerrainHeigth * coreInstance->zoom + coreInstance->winwowHeigth / 2) - (coreInstance->terrainHeigth * coreInstance->caseTerrainHeigth / 2 * coreInstance->zoom),
					(x * coreInstance->caseTerrainWidth * coreInstance->zoom + coreInstance->winwowWidth / 2) - (coreInstance->terrainWidth * coreInstance->caseTerrainWidth / 2 * coreInstance->zoom),
					coreInstance->caseTerrainWidth * coreInstance->zoom,
					coreInstance->caseTerrainHeigth * coreInstance->zoom
					};
					coreInstance->arrayGame[y][x].justChanged = false;
					SDL_SetRenderDrawColor(renderer, coreInstance->arrayGame[y][x].color.r, coreInstance->arrayGame[y][x].color.g, coreInstance->arrayGame[y][x].color.b, coreInstance->arrayGame[y][x].color.a);
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	return EXIT_SUCCESS;
}