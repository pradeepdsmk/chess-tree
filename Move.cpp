#include "Move.h"

namespace chess {

    Move::Move() {
        
        piece = promotedTo = capturedPiece = '\0';

        srcRow = srcCol = dstRow = dstCol = 8;

        isShortCastle = isLongCastle = isCapture = isEnpassant = false;
    }

	std::string Move::toString() {

		if (isShortCastle) {
			return std::string("O-O");
		}

		if (isLongCastle) {
			return std::string("O-O-O");
		}
		char str[8] = { 0 };

		if (isCapture) {
			if (piece == 'P') {
				sprintf_s(str, "%cx%c%c", 'a' + srcCol, 'a' + dstCol, 7 - dstRow + '1');
			}
			else {
				sprintf_s(str, "x%c%c", 'a' + dstCol, 7 - dstRow + '1');
			}
		}
		else {
			sprintf_s(str, "%c%c", 'a' + dstCol, 7 - dstRow + '1');
		}


		if (piece == 'P') {
			if (isEnpassant) {
				sprintf_s(str, "%se.p.", str);
			}
			else if (promotedTo != '\0') {
				sprintf_s(str, "%s=%c", str, promotedTo);
			}
		}
		else {
			sprintf_s(str, "%s", str);

			if (srcRow < 8) {
				sprintf_s(str, "%c%s", 7 - srcRow + '1', str);
			}

			if (srcCol < 8) {
				sprintf_s(str, "%c%s", 'a' + srcCol, str);
			}

			sprintf_s(str, "%c%s", piece, str);
		}

		return std::string(str);
	}
}