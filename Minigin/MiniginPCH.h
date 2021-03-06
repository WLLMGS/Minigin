#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Log.h" // Various logging functions

using namespace std;

//#define DEBUG

namespace GameSettings
{
	const float WindowSizeX = 512.0f;
	const float WindowSizeY = 512.0f;
	const float TileSize = 32.0f;
	const int FontSize = 24;
}
