#pragma once
#include "GraphicEngine.h"
#include "Struct.h"

class Core;
class Ant
{
public:
	Ant(Core *, Color, Color, int, int);
	~Ant();
	e_dir TurnLeft();
	e_dir TurnRight();
	void Move();

	Core * coreInstance;
	Color colorAnt;
	Color colorState;
	e_dir dir;
	int yStart;
	int xStart;
	int yCurrent;
	int xCurrent;
};

