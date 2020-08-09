#include "Move.h"

Move::Move() : PawnMoves(), KnightMoves(), QueenMoves(), KingMoves()
{
}

Move::~Move()
{
}

void Move::ChessManPossibleMoves(string const actualPosition)
{
    std::list<string> possibleMoves;
    char file(actualPosition[0]);
    char rank(actualPosition[1]);

    ChessMan movedChessMan(boardAttributes.boardState.at(actualPosition));

    ChessManType chessManType(movedChessMan.GetType());
    switch (chessManType)
    {
    case ChessManType::None:
        break;
    case ChessManType::Rook:
        RookPossibleMoves(
            boardAttributes.boardState,
            boardAttributes.movesBoard,
            boardAttributes.reactionBoard,
            actualPosition,
            movedChessMan,
            file,
            rank
        );
        break;
    case ChessManType::Knight:
        KnightPossibleMoves(
            boardAttributes.boardState,
            boardAttributes.movesBoard,
            boardAttributes.reactionBoard,
            actualPosition,
            movedChessMan,
            file,
            rank
        );
        break;
    case ChessManType::Bishop:
        BishopPossibleMoves(
            boardAttributes.boardState,
            boardAttributes.movesBoard,
            boardAttributes.reactionBoard,
            actualPosition,
            movedChessMan,
            file,
            rank
        );
        break;
    case ChessManType::Queen:
        QueenPossibleMoves(
            boardAttributes.boardState,
            boardAttributes.movesBoard,
            boardAttributes.reactionBoard,
            actualPosition,
            movedChessMan,
            file,
            rank
        );
        break;
    case ChessManType::King:
        KingPossibleMoves(
            boardAttributes.boardState,
            boardAttributes.movesBoard,
            boardAttributes.reactionBoard,
            actualPosition,
            movedChessMan,
            file,
            rank
        );
        break;
    case ChessManType::Pawn:
        PawnPossibleMoves(
            boardAttributes.boardState,
            boardAttributes.movesBoard,
            boardAttributes.reactionBoard,
            actualPosition,
            movedChessMan,
            file,
            rank
        );
        break;
    default:
        break;
    }
}
