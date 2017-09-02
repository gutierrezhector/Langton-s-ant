#pragma once
#include <sstream>

enum e_state { STATE0, STATE1 };
enum e_dir { TOP, RIGHT, BOT, LEFT };

struct Color
{
	char r;
	char g;
	char b;
	char a;
};

struct Case
{
	Color color;
	e_state state;
	bool justChanged;

	std::string ToString()
	{
		std::stringstream ss;

		ss << "r: " << color.r << ", g: " << color.g << ", b: " << color.b << ", a: " << color.a;
		return ss.str();
	}
};
