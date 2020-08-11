// ChessTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <Windows.h>
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

	std::string input, output;

	chess::Engine engine;
	chess::XboardCommand command(engine);

	while (1) {
		Sleep(200); // for some reason

		std::getline(std::cin, input);
		Log::add("input: " + input);

		if (command.process(input, output) == false) {
			break;
		}

		Log::add("output: " + output);

		if (!output.empty()) {
			std::cout << output << std::endl;
		}
	}
}

int main()
{
	Log::begin();

	idea3();

	Log::end();

	return 0;
}