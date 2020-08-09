#include "RookMoves.h"

RookMoves::RookMoves() : UpdateAttributes()
{
}

RookMoves::~RookMoves()
{
}

void RookMoves::CheckRookMovesAndUpdateReactionBoard(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string const actualPosition,
    ChessMan const movedChessMan,
    char const file,
    char const rank,
    string const file_range,
    string const rank_range
)
{
    int fileIndex(file_range.find(file));
    for (auto file_it = file_range.begin() + fileIndex + 1; file_it != file_range.end(); file_it++)
    {
        string possiblePosition(ConvertFileAndRankToPosition(*file_it, rank));

        if (LookForPossibleMoveAndUpdateReactionBoard(
            boardState,
            movesBoard,
            reactionBoard,
            actualPosition,
            possiblePosition,
            movedChessMan
        ))
            break;
    }

    int rankIndex(rank_range.find(rank));
    for (auto rank_it = rank_range.begin() + rankIndex + 1; rank_it != rank_range.end(); rank_it++)
    {
        string possiblePosition(ConvertFileAndRankToPosition(file, *rank_it));

        if (LookForPossibleMoveAndUpdateReactionBoard(
            boardState,
            movesBoard,
            reactionBoard,
            actualPosition,
            possiblePosition,
            movedChessMan
        ))
            break;
    }

}

void RookMoves::RookPossibleMoves(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string const actualPosition,
    ChessMan const movedChessMan,
    char const file,
    char const rank
)
{
    CheckRookMovesAndUpdateReactionBoard(
        boardState,
        movesBoard,
        reactionBoard,
        actualPosition,
        movedChessMan,
        file,
        rank,
        fileRange,
        rankRange
    );
    CheckRookMovesAndUpdateReactionBoard(
        boardState,
        movesBoard,
        reactionBoard, 
        actualPosition,
        movedChessMan,
        file,
        rank,
        inverted_fileRange,
        inverted_rankRange
    );
}
