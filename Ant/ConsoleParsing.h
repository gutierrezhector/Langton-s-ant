#pragma once
#include <string>
#include <iostream>
#include <istream>
#include <vector>
#include <cctype>

#include "Core.h"

class Core;
class GraphicEngine;
class ConsoleParsing
{
private:
	Core * instanceCore;
	GraphicEngine * instanceGraphicEngine;

	bool VerifAdd(std::vector<std::string>);
	bool VerifSpeed(std::vector<std::string>);
	bool VerifZoom(std::vector<std::string>);

public:
	bool isRunning;

	ConsoleParsing(Core *, GraphicEngine *);
	~ConsoleParsing();

	std::vector<std::string> ParsArg(std::string);
	void Update();
};

