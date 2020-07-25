// ChessTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <chrono>
#include "Board.h"
#include <Windows.h>
#include <queue>
#include "Log.h"
#include "Engine.h"
#include "XboardCommand.h"


#ifdef _WIN32
#define CMD_CLEAR_SCREEN "cls"
#elif
#define CMD_CLEAR_SCREEN "clear"
#endif

typedef std::chrono::high_resolution_clock::time_point Timepoint;

void idea3() {

	std::queue<std::string> log;

	std::string input, output;

	chess::Engine engine;
	chess::XboardCommand command(engine);

	while (1) {
		Sleep(100); // for some reason

		std::getline(std::cin, input);
		Log::add("input: " + input);

		if (command.process(input, output) == false) {
			break;
		}

		Log::add("output: " + output);

		std::cout << output << std::endl;
	}
}

int main()
{
	Log::begin();

	idea3();

	Log::end();

	return 0;
}