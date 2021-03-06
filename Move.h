#pragma once

#include <string>
#include "Constants.h"
#include "Square.h"

namespace chess {

	class Square;

	class Move
	{		

	public:
		//std::string s;
		char piece, capturedPiece, promotedTo;
		unsigned char srcRow, srcCol, dstRow, dstCol;
		char moveFlags;
		static const char SHORT_CASTLE = 0x01;
		static const char LONG_CASTLE = 0x02;
		static const char ENPASSANT = 0x04;
		static const char COLOR_WHITE = 0x08;
		

		//bool isShortCastle;
		//bool isLongCastle;
		//bool isCapture;
		//bool isEnpassant;
		//Color color;
		char score;
		
		

		Move();	

		static inline bool isRow(const char& c) {
			return ((c >= '1') && (c <= '8'));
		}

		static inline bool isCol(const char& c) {
			return ((c >= 'a') && (c <= 'h'));
		}

		static inline unsigned getRow(const char& c) {
			return (7 - (c - '1'));
		}

		static inline unsigned getCol(const char& c) {
			return (c - 'a');
		}

		std::string toSAN();
		std::string toLAN();

		bool fromSAN(const char* str);
		bool fromLAN(const char* str);

		Move* clone();
	};
}