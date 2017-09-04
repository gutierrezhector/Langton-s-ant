#include "ConsoleParsing.h"

ConsoleParsing::ConsoleParsing(Core * newCore, GraphicEngine * newGraphicEngine)
{
	instanceCore = newCore;
	instanceGraphicEngine = newGraphicEngine;
	isRunning = true;
}


ConsoleParsing::~ConsoleParsing()
{

}

std::vector<std::string> ConsoleParsing::ParsArg(std::string argLine)
{
	char delimiter = ' ';
	std::stringstream ss(argLine);
	std::string item;
	std::vector<std::string> args;
	std::string::size_type stTemp = argLine.find(delimiter);

	while (stTemp != std::string::npos)
	{
		args.push_back(argLine.substr(0, stTemp));
		argLine = argLine.substr(stTemp + (argLine.find_first_not_of(' ', stTemp) - stTemp));
		stTemp = argLine.find(delimiter);
	}

	args.push_back(argLine);
	return args;
}

void ConsoleParsing::Update()
{
	std::string argLine;

	while (isRunning)
	{
		std::cout << "Ant [speed: " << instanceCore->speed << " - zoom: " << instanceCore->zoom << "] >" << std::flush;
		getline(std::cin, argLine);
		std::vector<std::string> args = ParsArg(argLine);

		if (args[0].compare("pause") == 0 ||
			args[0].compare("p") == 0)
		{
			if (instanceCore->isPaused)
			{
				std::cout << "Unpause" << std::endl;
				instanceCore->isPaused = false;
			}
			else
			{
				std::cout << "Pause" << std::endl;
				instanceCore->isPaused = true;
			}
		}

		if (args[0].compare("add") == 0 ||
			args[0].compare("a") == 0)
		{
			if (VerifAdd(args))
			{
				instanceCore->AddAnt(std::stoi(args[1]), std::stoi(args[2]));
				std::cout << "Add ant to y: " << args[1] << ", x: " << args[2]  << std::endl;
			}
		}

		if (args[0].compare("speed") == 0 ||
			args[0].compare("s") == 0)
		{
			if (VerifSpeed(args))
			{
				instanceCore->speed = std::stof(args[1]);
				std::cout << "Speed to " << instanceCore->speed << std::endl;
			}
		}

		if (args[0].compare("zoom") == 0 ||
			args[0].compare("z") == 0)
		{
			if (VerifZoom(args))
			{
				instanceCore->zoom = std::stof(args[1]);
				std::cout << "Zoom to " << instanceCore->zoom << std::endl;
				instanceGraphicEngine->RefreshWindow();
			}
		}

		if (args[0].compare("quit") == 0 ||
			args[0].compare("exit") == 0 ||
			args[0].compare("e") == 0 ||
			args[0].compare("q") == 0)
		{
			instanceCore->isRunning = false;
			instanceGraphicEngine->isRunning = false;
			isRunning = false;
		}
		if (args[0].compare("help") == 0 ||
			args[0].compare("h") == 0)
		{
			std::cout << "Command:\n\n\tpause/p: pause the process if it is running and unpause it if it is not\n\n\tadd/a <y> <x>: add an ant at the gave position\n\n\tspeed/s <number>: multiply the speed of the process.\n\n\tzoom/z <number>: modify the zoom in the graphic interface\n\n\tquit/exit/e/q: exit the program\n" << std::endl;
		}
	}
}

bool ConsoleParsing::VerifAdd(std::vector<std::string> args)
{
	if (args.size() < 3)
	{
		std::cout << "Usage: add/a <position y> <position x>" << std::endl;
		return false;
	}
	std::string::const_iterator it = args[1].begin();
	for (std::string::const_iterator it = args[1].begin(); it != args[1].end(); ++it)
		if (std::isdigit(*it) == 0)
		{
			std::cout << "Enter a correct number" << std::endl;
			return false;
		}
	it = args[2].begin();
	for (std::string::const_iterator it = args[2].begin(); it != args[2].end(); ++it)
		if (std::isdigit(*it) == 0)
		{
			std::cout << "Enter a correct number" << std::endl;
			return false;
		}
	if (std::stof(args[1]) > (float)1000)
	{
		std::cout << "Number too hight" << std::endl;
		return false;
	}
	return true;
}

bool ConsoleParsing::VerifSpeed(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		std::cout << "Usage: speed/s <number>" << std::endl;
		return false;
	}
	std::string::const_iterator it = args[1].begin();
	for (std::string::const_iterator it = args[1].begin(); it != args[1].end(); ++it)
		if (std::isdigit(*it) == 0)
		{
			std::cout << "Enter a correct number" << std::endl;
			return false;
		}
	if (std::stof(args[1]) > (float)1000000)
	{
		std::cout << "Number too hight" << std::endl;
		return false;
	}
	return true;
}

bool ConsoleParsing::VerifZoom(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		std::cout << "Usage: zoom/z <number>" << std::endl;
		return false;
	}
	std::string::const_iterator it = args[1].begin();
	for (std::string::const_iterator it = args[1].begin(); it != args[1].end(); ++it)
		if (std::isdigit(*it) == 0 && *it != '.')
		{
			std::cout << "Enter a correct number" << std::endl;
			return false;
		}
	if (std::stof(args[1]) > (float)10)
	{
		std::cout << "Number too hight" << std::endl;
		return false;
	}
	return true;
}
