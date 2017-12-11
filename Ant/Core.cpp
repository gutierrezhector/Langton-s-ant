#include "Core.h"

const static Color arrayColorAnt[] = {
	{ (char)255, (char)0, (char)0, (char)255 },
	{ (char)0, (char)0, (char)255, (char)255 },
	{ (char)255, (char)255, (char)0, (char)255 },
	{ (char)0, (char)255, (char)0, (char)255 }
};

const static Color arrayColorState[] = {
	{ (char)0, (char)0, (char)255, (char)255 },
	{ (char)255, (char)0, (char)0, (char)255 },
	{ (char)0, (char)255, (char)0, (char)255 },
	{ (char)255, (char)255, (char)0, (char)255 }
};

Core::Core()
{
	speedDefault = 1000000000;
	colorStateDefault = { (char)0, (char)0, (char)0, (char)255 };
	isRunning = true;
	clockFlag = 0;
	isPaused = false;
	offsetAnt = 0;
}


Core::~Core()
{
	for (int y = 0; y < terrainHeight; y++)
		delete arrayGame[y];
	delete arrayGame;
}

void Core::ResetArrayGame()
{
	for (int y = 0; y < terrainHeight; y++)
	{
		for (int x = 0; x < terrainWidth; x++)
		{
			arrayGame[y][x].color = { 0, 0, 0, 1 };
			arrayGame[y][x].state = e_state::STATE0;
			arrayGame[y][x].justChanged = false;
		}
	}
}

bool Core::ConfigFile()
{
	std::ifstream file("config", std::ios::in);

	if (file)
	{
		std::string line;
		std::stringstream ss;
		std::string item;
		std::vector<std::string> args;
		std::string::size_type stTemp;
		char delimiter = ' ';
		while (getline(file, line))
		{
			std::stringstream ss(line);
			stTemp = line.find(delimiter);
			while (stTemp != std::string::npos)
			{
				args.push_back(line.substr(0, stTemp));
				line = line.substr(stTemp + (line.find_first_not_of(' ', stTemp) - stTemp));
				stTemp = line.find(delimiter);
			}
			args.push_back(line);
			if (args.size() < 4)
			{
				if (args[0].compare("#ant") == 0)
				{
					std::cout << "Add ant to y: " << args[1] << ", x: " << args[2] << std::endl;
					AddAnt(std::stoi(args[1]), std::stoi(args[2]));
				}
				if (args[0].compare("#s") == 0)
				{
					std::cout << "Speed to " << args[1] << std::endl;
					speed = std::stof(args[1]);
				}
				if (args[0].compare("#ww") == 0)
				{
					std::cout << "Window width to " << args[1] << std::endl;
					windowWidth = std::stoi(args[1]);
				}
				if (args[0].compare("#wh") == 0)
				{
					std::cout << "Window heigth to " << args[1] << std::endl;
					windowHeight = std::stoi(args[1]);
				}
				if (args[0].compare("#ctw") == 0)
				{
					std::cout << "Case terrain width to " << args[1] << std::endl;
					caseTerrainWidth = std::stoi(args[1]);
				}
				if (args[0].compare("#cth") == 0)
				{
					std::cout << "Case terrain heigth to " << args[1] << std::endl;
					caseTerrainHeight = std::stoi(args[1]);
				}
				if (args[0].compare("#tw") == 0)
				{
					std::cout << "Terrain width to " << args[1] << std::endl;
					terrainWidth = std::stoi(args[1]);
				}
				if (args[0].compare("#th") == 0)
				{
					std::cout << "Terrain heigth to " << args[1] << std::endl;
					terrainHeight = std::stoi(args[1]);
				}
				if (args[0].compare("#z") == 0)
				{
					std::cout << "Zoom to " << args[1] << std::endl;
					zoom = std::stof(args[1]);
				}
			}
			args.clear();
		}
		file.close();
	}
	else
	{
		std::cerr << "Problem open config file" << std::endl;
		return false;
	}
	return true;
}

bool Core::Init()
{
	if (!ConfigFile())
		return false;
	arrayGame = new Case*[terrainHeight];
	for (int y = 0; y < terrainHeight; y++)
	{
		arrayGame[y] = new Case[terrainWidth];
		for (int x = 0; x < terrainWidth; x++)
		{
			arrayGame[y][x].color = {0, 0, 0, 1};
			arrayGame[y][x].state = e_state::STATE0;
			arrayGame[y][x].justChanged = false;
			arrayGame[y][x].y = y;
			arrayGame[y][x].x = x;
		}
	}
	return true;;
}

void Core::DoOneStep()
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
	currentStep++;
}

void Core::Update()
{
	auto start = std::chrono::high_resolution_clock::now() - std::chrono::nanoseconds((speedDefault / (speed * speed)));
	while (isRunning)
	{
		if (!isPaused)
		{
			auto tick = std::chrono::high_resolution_clock::now();
			if (std::chrono::duration_cast<std::chrono::nanoseconds>(tick - start).count() >= (speedDefault / (speed * speed)))
			{
				DoOneStep();
				start = std::chrono::high_resolution_clock::now();
			}
		}
	}
}

bool Core::AddAnt(int y, int x)
{
	antPlayers.push_back(CreateAnt(y, x));
	offsetAnt = offsetAnt + 1 == 4 ? 0 : offsetAnt + 1;
	return true;
}

Ant * Core::CreateAnt(int y, int x)
{
	Ant* ant1 = new Ant(this, arrayColorAnt[offsetAnt], arrayColorState[offsetAnt], y, x);
	return ant1;
}

void Core::PrintArray()
{
	for (int y = 0; y < caseTerrainHeight; y++)
	{
		for (int x = 0; x < caseTerrainWidth; x++)
		{
			std::cout << "state[" << y << "][" << x << "] : " << arrayGame[y][x].ToString() << std::endl;
		}
	}
}
