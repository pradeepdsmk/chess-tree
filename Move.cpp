#include "Move.h"


namespace chess {
    Move::Move(Pieces::PieceTypes _pieceType, Square* _srcSquare, Square* _dstSquare)
    {
        pieceType = _pieceType;
        srcSquare = _srcSquare;
        dstSquare = _dstSquare;
    }
}