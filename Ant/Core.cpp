#include "Core.h"

const static Color arrayColorAnt[] = {
	{ (char)255, (char)0, (char)0, (char)1 },
	{ (char)0, (char)0, (char)255, (char)1 },
	{ (char)255, (char)255, (char)0, (char)1 },
	{ (char)0, (char)255, (char)0, (char)1 }
};

const static Color arrayColorState[] = {
	{ (char)0, (char)0, (char)255, (char)1 },
	{ (char)255, (char)0, (char)0, (char)1 },
	{ (char)0, (char)255, (char)0, (char)1 },
	{ (char)255, (char)255, (char)0, (char)1 }
};

Core::Core()
{
	speed = 1;
	speedDefault = 1000000000;
	winwowWidth = 1000;
	winwowHeigth = 1000;
	caseTerrainWidth = 10;
	caseTerrainHeigth = 10;
	terrainWidth = 500;
	terrainHeigth = 500;
	zoom = 0.5;
	colorStateDefault = { (char)0, (char)0, (char)0, (char)255 };
	isRunning = true;
	clockFlag = 0;
	isPaused = false;
	offsetAnt = 0;
}


Core::~Core()
{
	for (int y = 0; y < terrainHeigth; y++)
		delete arrayGame[y];
	delete arrayGame;
}

void Core::Init()
{

	arrayGame = new Case*[terrainHeigth];
	for (int y = 0; y < terrainHeigth; y++)
	{
		arrayGame[y] = new Case[terrainWidth];
		for (int x = 0; x < terrainWidth; x++)
		{
			arrayGame[y][x].color = {0, 0, 0, 1};
			arrayGame[y][x].state = e_state::STATE0;
			arrayGame[y][x].justChanged = false;
		}
	}
	/*Ant* ant1 = new Ant(this, Color { (char)255, (char)0, (char)0, (char)1 }, Color { (char)0, (char)255, (char)0, (char)1 }, 0, 0);
	Ant* ant2 = new Ant(this, Color{ (char)0, (char)255, (char)0, (char)1 }, Color{ (char)0, (char)0, (char)255, (char)1 }, 0, 50);
	Ant* ant3 = new Ant(this, Color{ (char)102, (char)0, (char)102, (char)1 }, Color{ (char)255, (char)0, (char)102, (char)1 }, 10, 10);
	Ant* ant4 = new Ant(this, Color{ (char)153, (char)102, (char)51, (char)1 }, Color{ (char)255, (char)153, (char)51, (char)1 }, 0, 150);

	Ant* ant5 = new Ant(this, Color{ (char)255, (char)0, (char)0, (char)1 }, Color{ (char)0, (char)255, (char)0, (char)1 }, 100, 100);
	Ant* ant6 = new Ant(this, Color{ (char)0, (char)255, (char)0, (char)1 }, Color{ (char)0, (char)0, (char)255, (char)1 }, 200, 200);
	Ant* ant7 = new Ant(this, Color{ (char)102, (char)0, (char)102, (char)1 }, Color{ (char)255, (char)0, (char)102, (char)1 }, 300, 350);
	Ant* ant8 = new Ant(this, Color{ (char)153, (char)102, (char)51, (char)1 }, Color{ (char)255, (char)153, (char)51, (char)1 }, 450, 450);

	antPlayers.push_back(ant1);
	antPlayers.push_back(ant2);
	antPlayers.push_back(ant3);
	antPlayers.push_back(ant4);
	antPlayers.push_back(ant5);
	antPlayers.push_back(ant6);
	antPlayers.push_back(ant7);
	antPlayers.push_back(ant8);*/
}

void Core::Update()
{
	while (isRunning)
	{
		if (!isPaused)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(speedDefault / (speed * speed)));
			std::list<Ant*>::const_iterator iterator;
			for (iterator = antPlayers.begin(); iterator != antPlayers.end(); ++iterator)
			{
				if (arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].state == e_state::STATE0) // case noir etat 0
				{
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].state = e_state::STATE1;
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].color = (*iterator)->colorState;
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].justChanged = true;
					(*iterator)->TurnLeft();
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].justChanged = true;
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].color = (*iterator)->colorAnt;
				}
				else // case blanche etat 1
				{
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].state = e_state::STATE0;
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].color = colorStateDefault;
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].justChanged = true;
					(*iterator)->TurnRight();
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].justChanged = true;
					arrayGame[(*iterator)->yCurrent][(*iterator)->xCurrent].color = (*iterator)->colorAnt;
				}
			}
		}
	}
}

bool Core::AddAnt(int y, int x)
{
	antPlayers.push_back(CreateAnt(y, x));
	offsetAnt++;
	return true;
}

Ant * Core::CreateAnt(int y, int x)
{
	Ant* ant1 = new Ant(this, arrayColorAnt[offsetAnt], arrayColorState[offsetAnt], y, x);
	return ant1;
}

bool Core::ChangeTerrainWidth()
{
	return false;
}

bool Core::ChangeTerrainHeigth()
{
	return false;
}

bool Core::ChangeZoom()
{
	return false;
}

bool Core::ChangeSpeed()
{
	return false;
}

void Core::PrintArray()
{
	for (int y = 0; y < caseTerrainHeigth; y++)
	{
		for (int x = 0; x < caseTerrainWidth; x++)
		{
			std::cout << "state[" << y << "][" << x << "] : " << arrayGame[y][x].ToString() << std::endl;
		}
	}
}
