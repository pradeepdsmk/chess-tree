#include <string.h>
#include "Move.h"
#include <sstream>

namespace chess {

    Move::Move() {
        
        piece = promotedTo = capturedPiece = NoPiece;

        srcRow = srcCol = dstRow = dstCol = 8;

        isShortCastle = isLongCastle = isCapture = isEnpassant = false;
    }

	std::string Move::toSAN() {

        std::stringstream ss;

		if (isShortCastle) {
			return std::string("O-O");
		}

		if (isLongCastle) {
			return std::string("O-O-O");
		}

		if (isCapture) {
			if ((piece == 'P') || (piece == 'p')) {
                ss << (char)('a' + srcCol) << 'x' << (char)('a' + dstCol) << (char)(7 - dstRow + '1');
			}
			else {
                ss << 'x' << (char)('a' + dstCol) << (char)(7 - dstRow + '1');
			}
		}
		else {
            ss << (char)('a' + dstCol) << (char)(7 - dstRow + '1');
		}


		if ((piece == 'P') || (piece == 'p')) {
			if (isEnpassant) {
                ss << "e.p.";
			}
			else if (promotedTo != NoPiece) {
                ss << '=' << promotedTo;
			}
            return ss.str();
		}
		else {
            std::stringstream sss;
            sss << piece << (char)('a' + srcCol) << (char)(7 - srcRow + '1') << ss.str();
            return sss.str();
		}       
	}

	std::string Move::toLAN() {
		char str[8] = { 0 };
		sprintf_s(str, "%c%c%c%c", 'a' + srcCol, 7 - srcRow + '1', 'a' + dstCol, 7 - dstRow + '1');
		return std::string(str);
	}

    bool Move::fromSAN(const char* str) {
        size_t len = strlen(str), pos = len, i;

        // find destination square, scan from end
        for (i = len - 2, pos = len; i >= 0; --i) {
            if (Move::isCol(str[i]) && Move::isRow(str[i + 1])) {
                pos = i;
                break;
            }
        }

        if (pos == len) {
            // may be it's castling move
            if (strcmp("O-O", str) == 0) {
                isShortCastle = true;
            }
            else if (strcmp("O-O-O", str) == 0) {
                isLongCastle = true;
            }
            else {
                //error = "Unable to decode, destination square not found\n";
                return false;
            }

            return true;
        }

        dstRow = Move::getRow(str[pos + 1]);
        dstCol = Move::getCol(str[pos]);

        // identify capture
        if ((pos >= 2) && (str[pos - 1] == 'x')) {
            //it's a capture
            isCapture = true;
        }

        // check promotion
        if ((len >= pos + 4) && (str[pos + 2] == '=')) {
            promotedTo = str[pos + 3];
        }

        //identify source piece and also possibly source square row or coumn or both
        switch (pos) {
        case 0:
            // pawn move-> ex: e4
            piece = 'P';
            break;
        case 1:
            // piece move-> ex: Nf3
            piece = str[0];
            break;
        case 2:
            // pawn capture, piece capture, ambiguous piece move-> ex: exf4, Bxc6, Rad1/R1d2
            if (Move::isCol(str[0])) {
                piece = 'P';
                srcCol = Move::getCol(str[0]);
            }
            else {
                piece = str[0];
                if (Move::isCol(str[1])) {
                    srcCol = Move::getCol(str[1]);
                }
                else if (Move::isRow(str[1])) {
                    srcRow = Move::getRow(str[1]);
                }
                else if (str[1] == 'x') {

                }
                else {
                    return false;
                }
            }

            break;
        case 3:
            //ambiguous piece capture, double ambiguous piece move-> ex: Raxd1/R1xd2, Qh4e1
            piece = str[0];
            if (Move::isCol(str[1])) {
                srcCol = Move::getCol(str[1]);
                if (Move::isRow(str[2])) {
                    srcRow = Move::getRow(str[2]);
                }
            }
            else if (Move::isRow(str[1])) {
                srcRow = Move::getRow(str[1]);
            }
            else {
                //error = "Invalid Move \n";
                return false;
            }
            break;
        case 4:
            //double ambiguous piece capture. ex: Qh4xe1
            piece = str[0];
            if (Move::isCol(str[1]) && Move::isRow(str[2])) {
                srcCol = Move::getCol(str[1]);
                srcRow = Move::getRow(str[2]);
            }
            else {
                return false;
            }
            break;
        }

        return true;
    }

    bool Move::fromLAN(const char* str) {
        srcCol = Move::getCol(str[0]);
        srcRow = Move::getRow(str[1]);

        dstCol = Move::getCol(str[2]);
        dstRow = Move::getRow(str[3]);

        if ((strcmp(str, "e1g1") == 0) || (strcmp(str, "e8g8") == 0)) {
            isShortCastle = true;
        }
        else if ((strcmp(str, "e1c1") == 0) || (strcmp(str, "e8c8") == 0)) {
            isLongCastle = true;
        }

        if (strlen(str) == 5) {
            promotedTo = str[4];
        }

        return true;
    }

    Move* Move::clone() {
        // to-do: may be copy constructor?
        Move* move = new Move();
        move->srcRow = srcRow;
        move->srcCol = srcCol;
        move->dstRow = dstRow;
        move->dstCol = dstCol;
        move->piece = piece;
        move->promotedTo = promotedTo;
        move->capturedPiece = capturedPiece;
        move->isShortCastle = isShortCastle;
        move->isLongCastle = isLongCastle;
        move->isCapture = isCapture;
        move->isEnpassant = isEnpassant;
        move->color = color;
        return move;
    }

}