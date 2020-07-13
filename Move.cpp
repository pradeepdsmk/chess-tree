#include "Move.h"
#include "Position.h"

chess::Move::Move(Position* p, const char* str)
{
	prevPosition = p;
	nextPosition = new chess::Position();
}

bool chess::Move::execute()
{
	return false;
}

float chess::Move::evaluate()
{
	return 0.0f;
}

chess::Position* chess::Move::getNextPosition()
{
	return nextPosition;
}
