#include "GraphicEngine.h"

#include <windows.h>
#include <string>
#include <iostream>
GraphicEngine::GraphicEngine(Core* newCore)
{
	coreInstance = newCore;
	offsettime = 0;
	isRunning = true;
	isPaused = true;
	justRefreshed = false;
	colorFont = { 255, 255, 255, 255 };
}


GraphicEngine::~GraphicEngine()
{
	SDL_DestroyWindow(mainWindow);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

void GraphicEngine::RefreshWindow()
{
	mtx.lock();
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 1);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Rect rect = {
		(coreInstance->windowWidth / 2) - ((coreInstance->terrainWidth * coreInstance->caseTerrainWidth * coreInstance->zoom) / 2),
		(coreInstance->windowHeight / 2) - ((coreInstance->terrainHeight * coreInstance->caseTerrainHeight * coreInstance->zoom) / 2),
		coreInstance->caseTerrainWidth * coreInstance->terrainWidth * coreInstance->zoom,
		coreInstance->caseTerrainHeight * coreInstance->terrainHeight * coreInstance->zoom
	};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	justRefreshed = true;
	mtx.unlock();
}

void GraphicEngine::DrawOneTime()
{
	DrawWindow();
}

bool GraphicEngine::Init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "Erreur d'initialisation de TTF_Init : " << TTF_GetError() << std::endl;
		return false;
	}
	if ((font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 100)) == NULL)
	{
		std::cout << "Erreur de chargement de la police : " << TTF_GetError() << std::endl;
		return false;
	}
	mainWindow = SDL_CreateWindow("Anty", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, coreInstance->windowWidth, coreInstance->windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(mainWindow, -1, 0);
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 1);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Rect rect = {
		(coreInstance->windowWidth / 2) - ((coreInstance->terrainWidth * coreInstance->caseTerrainWidth * coreInstance->zoom) / 2),
		(coreInstance->windowHeight / 2) - ((coreInstance->terrainHeight * coreInstance->caseTerrainHeight * coreInstance->zoom) / 2),
		coreInstance->caseTerrainWidth * coreInstance->terrainWidth * coreInstance->zoom,
		coreInstance->caseTerrainHeight * coreInstance->terrainHeight * coreInstance->zoom
	};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	return true;
}

void GraphicEngine::DrawCustomText()
{
	surfaceText = TTF_RenderText_Solid(font, std::to_string(coreInstance->currentStep).c_str(), colorFont);
	text = SDL_CreateTextureFromSurface(renderer, surfaceText);
	SDL_Rect textRect; //create a rect
	textRect.x = 0;  //controls the rect's x coordinate 
	textRect.y = 0; // controls the rect's y coordinte
	textRect.w = 100; // controls the width of the rect
	textRect.h = 100; // controls the height of the rect
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &textRect);
	SDL_RenderCopy(renderer, text, NULL, &textRect);
	SDL_FreeSurface(surfaceText);
	SDL_DestroyTexture(text);
}

void GraphicEngine::DrawWindow()
{
	for (int y = 0; y < coreInstance->terrainHeight; y++)
	{
		for (int x = 0; x < coreInstance->terrainWidth; x++)
		{
			if (coreInstance->arrayGame[y][x].justChanged || justRefreshed)
			{
				SDL_Rect rect = {
					(x * coreInstance->caseTerrainWidth * coreInstance->zoom + coreInstance->windowWidth / 2) - (coreInstance->terrainWidth * coreInstance->caseTerrainWidth / 2 * coreInstance->zoom),
					(y * coreInstance->caseTerrainHeight * coreInstance->zoom + coreInstance->windowHeight / 2) - (coreInstance->terrainHeight * coreInstance->caseTerrainHeight / 2 * coreInstance->zoom),
					coreInstance->caseTerrainWidth * coreInstance->zoom,
					coreInstance->caseTerrainHeight * coreInstance->zoom
				};
				coreInstance->arrayGame[y][x].justChanged = false;
				mtx.lock();
				SDL_SetRenderDrawColor(renderer, coreInstance->arrayGame[y][x].color.r, coreInstance->arrayGame[y][x].color.g, coreInstance->arrayGame[y][x].color.b, coreInstance->arrayGame[y][x].color.a);
				SDL_RenderFillRect(renderer, &rect);
				//DrawCustomText();
				mtx.unlock();
			}
		}
	}
	mtx.lock();
	SDL_RenderPresent(renderer);
	mtx.unlock();
	justRefreshed = false;
}

void GraphicEngine::Update()
{
	while (isRunning)
	{
		if (!coreInstance->isPaused)
		{
			DrawWindow();
		}
	}
}