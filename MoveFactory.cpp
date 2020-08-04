#include "MoveFactory.h"

namespace chess {
    MoveFactory* MoveFactory::thisInstance = nullptr;

    MoveFactory::MoveFactory()
    {
        moves = new List<Move>();
    }

    Move* MoveFactory::createMove(const char* str) {
        if (!thisInstance) {
            thisInstance = new MoveFactory();
        }

        Move* move = new Move();
        if (str && thisInstance->parseStr(str, move)) {
            thisInstance->moves->append(move);
            return move;            
        }
        delete move;
        return nullptr;
    }

    bool MoveFactory::parseStr(const char* str, Move* move) {
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
                move->isShortCastle = true;
            }
            else if (strcmp("O-O-O", str) == 0) {
                move->isLongCastle = true;
            }
            else {
                //error = "Unable to decode, destination square not found\n";
                return false;
            }

            return true;
        }

        move->dstRow = Move::getRow(str[pos + 1]);
        move->dstCol = Move::getCol(str[pos]);

        // identify capture
        if ((pos >= 2) && (str[pos - 1] == 'x')) {
            //it's a capture
            move->isCapture = true;
        }

        // check promotion
        if ((len >= pos + 4) && (str[pos + 2] == '=')) {
            move->promotedTo = str[pos + 3];
        }

        //identify source piece and also possibly source square row or coumn or both
        switch (pos) {
        case 0:
            // pawn move-> ex: e4
            move->piece = 'P';
            break;
        case 1:
            // piece move-> ex: Nf3
            move->piece = str[0];
            break;
        case 2:
            // pawn capture, piece capture, ambiguous piece move-> ex: exf4, Bxc6, Rad1/R1d2
            if (Move::isCol(str[0])) {
                move->piece = 'P';
                move->srcCol = Move::getCol(str[0]);
            }
            else {
                move->piece = str[0];
                if (Move::isCol(str[1])) {
                    move->srcCol = Move::getCol(str[1]);
                }
                else if (Move::isRow(str[1])) {
                    move->srcRow = Move::getRow(str[1]);
                }
                else if (str[1] == 'x') {

                }
                else {
                    //error = "Invalid Move \n";
                    return false;
                }
            }

            break;
        case 3:
            //ambiguous piece capture, double ambiguous piece move-> ex: Raxd1/R1xd2, Qh4e1
            move->piece = str[0];
            if (Move::isCol(str[1])) {
                move->srcCol = Move::getCol(str[1]);
                if (Move::isRow(str[2])) {
                    move->srcRow = Move::getRow(str[2]);
                }
            }
            else if (Move::isRow(str[1])) {
                move->srcRow = Move::getRow(str[1]);
            }
            else {
                //error = "Invalid Move \n";
                return false;
            }
            break;
        case 4:
            //double ambiguous piece capture. ex: Qh4xe1
            move->piece = str[0];
            if (Move::isCol(str[1]) && Move::isRow(str[2])) {
                move->srcCol = Move::getCol(str[1]);
                move->srcRow = Move::getRow(str[2]);
            }
            else {
                //error = "Invalid Move \n";
                return false;
            }
            break;
        }

        return true;
    }

    MoveFactory::~MoveFactory()
    {
        if (thisInstance->moves) {
            delete thisInstance->moves;
        }
        delete thisInstance;
    }
}
