#include "Core.h"

Core::Core()
{
	zoom = 1;
	speed = 1;
	colorStateDefault = { (char)0, (char)0, (char)0, (char)255 };
}


Core::~Core()
{

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
	Ant* ant1 = new Ant(this, Color { (char)255, (char)0, (char)0, (char)1 }, Color { (char)0, (char)255, (char)0, (char)1 }, terrainHeigth / 2, terrainWidth / 2);
	Ant* ant2 = new Ant(this, Color{ (char)0, (char)255, (char)0, (char)1 }, Color{ (char)0, (char)0, (char)255, (char)1 }, terrainHeigth / 2 - 50, terrainWidth / 2 - 50);
	Ant* ant3 = new Ant(this, Color{ (char)102, (char)0, (char)102, (char)1 }, Color{ (char)255, (char)0, (char)102, (char)1 }, terrainHeigth / 2 - 60, terrainWidth / 2 + 85);
	Ant* ant4 = new Ant(this, Color{ (char)153, (char)102, (char)51, (char)1 }, Color{ (char)255, (char)153, (char)51, (char)1 }, 0, 0);

	antPlayers.push_back(ant1);
	antPlayers.push_back(ant2);
	antPlayers.push_back(ant3);
	antPlayers.push_back(ant4);
}

void Core::Update()
{
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
