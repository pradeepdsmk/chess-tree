#pragma once

#include <string>
#include "Square.h"

typedef unsigned char byte;

namespace chess {

	class Move
	{		

	public:
		char piece, capturedPiece, promotedTo;
		unsigned char srcRow, srcCol, dstRow, dstCol;

		bool isShortCastle;
		bool isLongCastle;
		bool isCapture;
		bool isEnpassant;

		Move();

		static inline std::string charToString(const char& c) {
			std::string s(1, ((c == '\0') ? ' ' : c));
			return s;
		}

		static inline std::string boolToString(const bool& c) {
			std::string s(1, (c ? '1' : '0'));
			return s;
		}

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

		std::string toString();
	};
}