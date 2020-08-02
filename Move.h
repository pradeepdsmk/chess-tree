#pragma once

#include "Square.h"

typedef unsigned char byte;

namespace chess {

	class Move
	{
		byte flags = 0;
		static const byte CaptureFlag = 0x1;
		static const byte CastleFlag = 0x2;
		static const byte LongCastle = 0x4;

	public:
		Square* srcSquare;
		Square* dstSquare;
		Pieces::PieceTypes pieceType;

		Pieces::PieceTypes capturedPieceType;
		byte moveInfoFlags;
		char moveStr[8] = { 0 };

		Move(Pieces::PieceTypes _pieceType, Square* _srcSquare, Square* _dstSquare);
	};


}