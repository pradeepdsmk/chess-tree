#include <string>

#include "Engine.h"
#include "XboardCommand.h"

chess::XboardCommand::XboardCommand(Engine& e): engine(e) {
	mapSize = sizeof(m) / sizeof(m[0]);
}

bool chess::XboardCommand::hXboard(const std::string& input, std::string& output) {
	output = "";
	return true;
}

bool chess::XboardCommand::hProtover(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hAccepted(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hRejected(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hNew(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hVariant(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hQuit(const std::string& input, std::string& output) {
	output = "";
	return false; // this is only place we return false
}

bool chess::XboardCommand::hRandom(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hForce(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hGo(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hPlayother(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hWhite(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hBlack(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hLevel(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hSt(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hSd(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hNps(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hTime(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hOtim(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hUsermove(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hQuestionmark(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hPing(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hDraw(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hResult(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hSetboard(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hEdit(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hHint(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hBk(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hUndo(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hRemove(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hHard(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hEasy(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hPost(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hNopost(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hAnalyze(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hName(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hRating(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hIcs(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hComputer(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hPause(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hResume(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hMemory(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hCores(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hEgtpath(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hOption(const std::string& input, std::string& output)
{
	output = "";
	return true;
}

bool chess::XboardCommand::hMove(const std::string& input, std::string& output) {
	engine.onMove(input, output);
	return true;
}

bool chess::XboardCommand::process(const std::string& input, std::string& output) {
	for (size_t i = 0; i < mapSize; ++i) {
		if (input.rfind(m[i].name, 0) == 0) {
			return (this->*(m[i].func))(input, output);
		}
	}

	// if we are here, then the command is probably a move
	return hMove(input, output);
}