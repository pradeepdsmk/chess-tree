#pragma once

typedef unsigned char byte;

namespace chess {
	class Position;

	class Move
	{
		byte src;
		byte dst;
		byte flags = 0;
		static const byte CaptureFlag = 0x1;
		static const byte CastleFlag = 0x2;
		static const byte LongCastle = 0x4;

		chess::Position* prevPosition;
		chess::Position* nextPosition;

	public:
		Move(chess::Position* p, const char* coordinateStr);

		bool execute();
		float evaluate();
		chess::Position* getNextPosition();
	};


}
