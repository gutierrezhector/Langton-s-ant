#pragma once
#include <iostream>
#include <thread>
#include <list>

#include "Struct.h"
#include "Ant.h"
class Ant;
class Core
{

public:
	int winwowWidth;
	int winwowHeigth;
	int caseTerrainWidth;
	int caseTerrainHeigth;
	int terrainWidth;
	int terrainHeigth;
	float zoom;
	float speed;
	Case** arrayGame;
	Color colorStateDefault;
	std::list<Ant*> antPlayers;

	Core();
	~Core();
	void Init();
	void Update();
	void PrintArray();
};

