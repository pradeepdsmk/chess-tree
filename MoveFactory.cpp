#include "MoveFactory.h"

namespace chess {
    MoveFactory::MoveFactory()
    {
    }

    Move* MoveFactory::createMove(Pieces::PieceTypes pieceType, Square* srcSquare, Square* dstSquare)
    {
        Move* move = new Move(pieceType, srcSquare, dstSquare);
        moves->append(move);
        return move;
    }

    MoveFactory::~MoveFactory()
    {
        if (moves) {
            delete moves;
            moves = nullptr;
        }
    }
}
