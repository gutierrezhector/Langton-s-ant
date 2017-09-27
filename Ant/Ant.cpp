#include "Ant.h"



Ant::Ant(Core * newCore, Color newColorAnt, Color newColorState, int newYStart, int newXStart)
{
	coreInstance = newCore;
	colorAnt = newColorAnt;
	colorState = newColorState;
	yStart = newYStart;
	xStart = newXStart;
	yCurrent = yStart;
	xCurrent = xStart;
	dir = e_dir::TOP;
}

Ant::~Ant()
{
}

e_dir Ant::TurnLeft()
{
	switch (dir)
	{
	case e_dir::TOP:
		dir = e_dir::LEFT;
		break;
	case e_dir::LEFT:
		dir = e_dir::BOT;
		break;
	case e_dir::BOT:
		dir = e_dir::RIGHT;
		break;
	case e_dir::RIGHT:
		dir = e_dir::TOP;
		break;
	}
	Move();
	return dir;
}

e_dir Ant::TurnRight()
{
	switch (dir)
	{
	case e_dir::TOP:
		dir = e_dir::RIGHT;
		break;
	case e_dir::RIGHT:
		dir = e_dir::BOT;
		break;
	case e_dir::BOT:
		dir = e_dir::LEFT;
		break;
	case e_dir::LEFT:
		dir = e_dir::TOP;
		break;
	}
	Move();
	return dir;
}

void Ant::Move()
{
	switch (dir)
	{
	case e_dir::TOP:
		if (yCurrent == coreInstance->terrainHeight - 1)
			yCurrent = 0;
		else
			yCurrent += 1;
		break;
	case e_dir::RIGHT:
		if (xCurrent == coreInstance->terrainWidth - 1)
			xCurrent = 0;
		else
			xCurrent += 1;
		break;
	case e_dir::BOT:
		if (yCurrent == 0)
			yCurrent = coreInstance->terrainHeight - 1;
		else
			yCurrent -= 1;
		break;
	case e_dir::LEFT:
		if (xCurrent == 0)
			xCurrent = coreInstance->terrainWidth - 1;
		else
			xCurrent -= 1;
		break;
	}

}
