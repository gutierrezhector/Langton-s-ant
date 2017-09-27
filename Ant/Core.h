#pragma once
#include <iostream>
#include <thread>
#include <list>
#include <thread>
#include <chrono>
#include <istream>
#include <string>
#include <fstream>
#include <vector>

#include "Struct.h"
#include "Ant.h"
class Ant;
class Core
{
private:
	int offsetAnt;

	Ant * CreateAnt(int, int);
	void DoOneStep();
	void ResetArrayGame();

public:

	int windowWidth;
	int windowHeight;
	int caseTerrainWidth;
	int caseTerrainHeight;
	int terrainWidth;
	int terrainHeight;
	float zoom;
	long speed;
	long speedDefault;
	Case** arrayGame;
	Color colorStateDefault;
	std::list<Ant*> antPlayers;
	bool isRunning;
	bool isPaused;
	int clockFlag;
	int currentStep;

	Core();
	~Core();
	bool Init();
	void GoToStep(int);
	void Update();
	bool ConfigFile();
	bool AddAnt(int, int);
	void PrintArray();
};

