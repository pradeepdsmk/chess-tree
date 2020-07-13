// ChessTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <chrono>
#include "Board.h"
#include <Windows.h>
#include <queue>
#include "Log.h"

#ifdef _WIN32
#define CMD_CLEAR_SCREEN "cls"
#elif
#define CMD_CLEAR_SCREEN "clear"
#endif


typedef std::chrono::high_resolution_clock::time_point Timepoint;
typedef long long Duration;

enum commandCodes {
	COMMAND_XBOARD = 0,
	COMMAND_PROTOVER,
	COMMAND_ACCEPTED,
	COMMAND_REJECTED,
	COMMAND_NEW,
	COMMAND_VARIANT,
	COMMAND_QUIT,
	COMMAND_RANDOM,
	COMMAND_FORCE,
	COMMAND_GO,
	COMMAND_PLAYOTHER,
	COMMAND_WHITE,
	COMMAND_BLACK,
	COMMAND_LEVEL,
	COMMAND_ST,
	COMMAND_SD,
	COMMAND_NPS,
	COMMAND_TIME,
	COMMAND_OTIM,
	COMMAND_USERMOVE,
	COMMAND_QUESTIONMARK ,
	COMMAND_PING,
	COMMAND_DRAW,
	COMMAND_RESULT,
	COMMAND_SETBOARD,
	COMMAND_EDIT,
	COMMAND_HINT,
	COMMAND_BK,
	COMMAND_UNDO,
	COMMAND_REMOVE,
	COMMAND_HARD,
	COMMAND_EASY,
	COMMAND_POST,
	COMMAND_NOPOST,
	COMMAND_ANALYZE,
	COMMAND_NAME,
	COMMAND_RATING,
	COMMAND_ICS,
	COMMAND_COMPUTER,
	COMMAND_PAUSE,
	COMMAND_RESUME,
	COMMAND_MEMORY,
	COMMAND_CORES,
	COMMAND_EGTPATH,
	COMMAND_OPTION
};

void respond(std::string response) {
	std::cout << response << std::endl;
}

void processCommand(int commandCode) {
	if (commandCode == commandCodes::COMMAND_XBOARD) {
		respond("");
	}	
}

const char* getEngineMove(std::string move) {
	if (move.compare("e2e4") == 0) {
		return "e7e5";
	}
	else if (move.compare("d2d4") == 0) {
		return "c7c5";
	}
	else {
		return "";
	}
}



void idea3() {

	std::vector<std::string> commands = { "xboard", "protover", "accepted", "rejected", "new", "variant", "quit", "random", "force", "go", "playother", "white", "black", "level", "st", "sd", "nps", "time", "otim", "usermove", "?", "ping", "draw", "result", "setboard", "edit", "hint", "bk", "undo", "remove", "hard", "easy", "post", "nopost", "analyze", "name", "rating", "ics", "computer", "pause", "resume", "memory", "cores", "egtpath", "option" };

	std::queue<std::string> log;

	std::string input;

	while (1) {
		Sleep(100); // for some reason

		std::getline(std::cin, input);
		Log::add(input);

		if (input.find("exit") != std::string::npos) {
			break;
		}

		std::string command;
		int i, commandsCount = (int)commands.size();
		bool commandProcessed = false;
		
		for (i = 0; i < commandsCount; i++) {
			std::string command = commands[i];
			if (input.rfind(command, 0) == 0) {
				// we have a command, process it
				processCommand(i);
				commandProcessed = true;
				break;
			}
		}

		if (!commandProcessed) {
			// move, i guess..
			std::string engineMove = getEngineMove(input);
			std::string response;
			size_t responseLength = engineMove.size();
			if (responseLength == 0) {
				response = "resign";
			}
			else if (responseLength > 5) {
				// some illegal move message, send it as it is
				response = engineMove;
			}
			else {
				response += "move " + engineMove;
			}
			respond(response);
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