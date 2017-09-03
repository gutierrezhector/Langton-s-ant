#pragma once
#include <iostream>
#include <thread>
#include <list>
#include <thread>
#include <chrono>

#include "Struct.h"
#include "Ant.h"
class Ant;
class Core
{
private:
	int offsetAnt;

	Ant * CreateAnt(int, int);

public:

	int winwowWidth;
	int winwowHeigth;
	int caseTerrainWidth;
	int caseTerrainHeigth;
	int terrainWidth;
	int terrainHeigth;
	float zoom;
	long speed;
	long speedDefault;
	Case** arrayGame;
	Color colorStateDefault;
	std::list<Ant*> antPlayers;
	bool isRunning;
	bool isPaused;
	int clockFlag;

	Core();
	~Core();
	void Init();
	void Update();
	bool AddAnt(int, int);
	bool ChangeTerrainWidth();
	bool ChangeTerrainHeigth();
	bool ChangeZoom();
	bool ChangeSpeed();
	void PrintArray();
};

