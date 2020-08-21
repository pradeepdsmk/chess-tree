#pragma once

#include <string>
#include "Engine.h"

namespace chess {
	class XboardCommand;

	typedef bool (XboardCommand::* CommandFunc)(const std::string& input, std::string& output);	

	class XboardCommand {

		struct CommandFuncMap {
			std::string name;
			CommandFunc func;
		};

		CommandFuncMap m[47] = {
				{"xboard", &XboardCommand::hXboard},
				{"protover", &XboardCommand::hProtover},
				{"accepted", &XboardCommand::hAccepted},
				{"rejected", &XboardCommand::hRejected},
				{"new", &XboardCommand::hNew},
				{"variant", &XboardCommand::hVariant},
				{"quit", &XboardCommand::hQuit},
				{"random", &XboardCommand::hRandom},
				{"force", &XboardCommand::hForce},
				{"go", &XboardCommand::hGo},
				{"playother", &XboardCommand::hPlayother},
				{"white", &XboardCommand::hWhite},
				{"black", &XboardCommand::hBlack},
				{"level", &XboardCommand::hLevel},
				{"st", &XboardCommand::hSt},
				{"sd", &XboardCommand::hSd},
				{"nps", &XboardCommand::hNps},
				{"time", &XboardCommand::hTime},
				{"otim", &XboardCommand::hOtim},
				{"usermove", &XboardCommand::hUsermove},
				{"?", &XboardCommand::hQuestionmark},
				{"ping", &XboardCommand::hPing},
				{"draw", &XboardCommand::hDraw},
				{"result", &XboardCommand::hResult},
				{"setboard", &XboardCommand::hSetboard},
				{"edit", &XboardCommand::hEdit},
				{"hint", &XboardCommand::hHint},
				{"bk", &XboardCommand::hBk},
				{"undo", &XboardCommand::hUndo},
				{"remove", &XboardCommand::hRemove},
				{"hard", &XboardCommand::hHard},
				{"easy", &XboardCommand::hEasy},
				{"post", &XboardCommand::hPost},
				{"nopost", &XboardCommand::hNopost},
				{"analyze", &XboardCommand::hAnalyze},
				{".", &XboardCommand::hDot},
				{"exit", &XboardCommand::hExit},
				{"name", &XboardCommand::hName},
				{"rating", &XboardCommand::hRating},
				{"ics", &XboardCommand::hIcs},
				{"computer", &XboardCommand::hComputer},
				{"pause", &XboardCommand::hPause},
				{"resume", &XboardCommand::hResume},
				{"memory", &XboardCommand::hMemory},
				{"cores", &XboardCommand::hCores},
				{"egtpath", &XboardCommand::hEgtpath},
				{"option", &XboardCommand::hOption}
		};

		size_t mapSize;

		Engine &engine;

		bool hXboard(const std::string& input, std::string& output);

		bool hProtover(const std::string& input, std::string& output);
		bool hAccepted(const std::string& input, std::string& output);
		bool hRejected(const std::string& input, std::string& output);
		bool hNew(const std::string& input, std::string& output);
		bool hVariant(const std::string& input, std::string& output);
		bool hQuit(const std::string& input, std::string& output);
		bool hRandom(const std::string& input, std::string& output);
		bool hForce(const std::string& input, std::string& output);
		bool hGo(const std::string& input, std::string& output);
		bool hPlayother(const std::string& input, std::string& output);
		bool hWhite(const std::string& input, std::string& output);
		bool hBlack(const std::string& input, std::string& output);
		bool hLevel(const std::string& input, std::string& output);
		bool hSt(const std::string& input, std::string& output);
		bool hSd(const std::string& input, std::string& output);
		bool hNps(const std::string& input, std::string& output);
		bool hTime(const std::string& input, std::string& output);
		bool hOtim(const std::string& input, std::string& output);
		bool hUsermove(const std::string& input, std::string& output);
		bool hQuestionmark(const std::string& input, std::string& output);
		bool hPing(const std::string& input, std::string& output);
		bool hDraw(const std::string& input, std::string& output);
		bool hResult(const std::string& input, std::string& output);
		bool hSetboard(const std::string& input, std::string& output);
		bool hEdit(const std::string& input, std::string& output);
		bool hHint(const std::string& input, std::string& output);
		bool hBk(const std::string& input, std::string& output);
		bool hUndo(const std::string& input, std::string& output);
		bool hRemove(const std::string& input, std::string& output);
		bool hHard(const std::string& input, std::string& output);
		bool hEasy(const std::string& input, std::string& output);
		bool hPost(const std::string& input, std::string& output);
		bool hNopost(const std::string& input, std::string& output);
		bool hAnalyze(const std::string& input, std::string& output);
		bool hDot(const std::string& input, std::string& output);
		bool hExit(const std::string& input, std::string& output);
		bool hName(const std::string& input, std::string& output);
		bool hRating(const std::string& input, std::string& output);
		bool hIcs(const std::string& input, std::string& output);
		bool hComputer(const std::string& input, std::string& output);
		bool hPause(const std::string& input, std::string& output);
		bool hResume(const std::string& input, std::string& output);		
		bool hMemory(const std::string& input, std::string& output);
		bool hCores(const std::string& input, std::string& output);
		bool hEgtpath(const std::string& input, std::string& output);
		bool hOption(const std::string& input, std::string& output);

		bool hMove(const std::string& input, std::string& output);


	public:

		XboardCommand(Engine& e);

		bool process(const std::string& input, std::string& output);

		~XboardCommand();
	};
}

