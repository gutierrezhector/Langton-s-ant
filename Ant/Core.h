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
	bool Init();
	void Update();
	bool ConfigFile();
	bool AddAnt(int, int);
	void PrintArray();
};

