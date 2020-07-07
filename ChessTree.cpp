// ChessTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <chrono>
#include "Board.h"

#ifdef _WIN32
#define CMD_CLEAR_SCREEN "cls"
#elif
#define CMD_CLEAR_SCREEN "clear"
#endif


typedef std::chrono::high_resolution_clock::time_point Timepoint;
typedef long long Duration;

void idea3() {

	Board b;	
	b.startpos();
	b.printToConsole();

	std::string input;
	Timepoint t1, t2;
	Duration duration;

	while (1) {

		std::cout << "> ";
		std::cin >> input;

		if (input.compare("exit") == 0) {
			break;
		}
		
		t1 = std::chrono::high_resolution_clock::now();

		bool execResult = b.execute(input.c_str());

		t2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

		if (execResult == true) {
			std::system(CMD_CLEAR_SCREEN);
			b.printToConsole();
		}		

		std::cout << "> Duration " << duration << " microseconds" << std::endl;

		if (!execResult) {
			std::cout << "> Invalid Move. (To end program, type exit)" << std::endl;
		}

	} 
}


int main()
{
	idea3();

	return 0;	
}