#include "PawnMoves.h"

PawnMoves::PawnMoves() : UpdateAttributes()
{
}

PawnMoves::~PawnMoves()
{
}

bool PawnMoves::LookForPawnPossibleMoves(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    string possiblePosition,
    string actualPosition
)
{
    ChessMan checkedField(boardState.at(possiblePosition));
    std::list<string>& possibleMoves(movesBoard.at(actualPosition));
    if (checkedField.GetColor() == 0)
    {
        possibleMoves.push_back(possiblePosition);
        return false;
    }
    return true;
}

void PawnMoves::LookForPawnPossibleCaptureAndUpdateReactionBoard(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string possiblePosition,
    string actualPosition,
    ChessMan movedChessMan
)
{
    ChessMan checkedField(boardState.at(possiblePosition));
    std::list<string>& possibleMoves(movesBoard.at(actualPosition));
    if (checkedField.GetColor() != 0)
    {
        if (checkedField.GetColor() != movedChessMan.GetColor())
        {
            possibleMoves.push_back(possiblePosition);
        }
    }
    UpdateReactionBoard(reactionBoard, possiblePosition, movedChessMan);
}

void PawnMoves::CheckPawnCaptures(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string actualPosition,
    ChessMan const movedChessMan,
    char const file,
    char const rank,
    string const file_range
)
{
    int fileIndex(file_range.find(file));
    auto file_it = file_range.begin() + fileIndex + 1;
    int step(1);

    string possibleCapture;
    for (file_it, step; file_it != file_range.end() && step < 2; step++)
    {
        possibleCapture = ConvertFileAndRankToPosition(*file_it, rank);
        LookForPawnPossibleCaptureAndUpdateReactionBoard(
            boardState,
            movesBoard,
            reactionBoard,
            possibleCapture,
            actualPosition,
            movedChessMan
        );
    }
}

void PawnMoves::PawnPossibleMoves(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string actualPosition,
    ChessMan movedChessMan,
    char const file,
    char const rank
)
{
    string rank_range;
    if (movedChessMan.CheckMoveDirection() == "increase")
    {
        rank_range = inverted_rankRange;
    }
    else
    {
        rank_range = rankRange;
    }

    int rankIndex(rank_range.find(rank));
    auto rank_it = rank_range.begin() + rankIndex + 1;
    int step(1);

    int steps;
    if (movedChessMan.CheckFirstMove()) steps = 2;
    else steps = 1;

    string possiblePosition;
    for (rank_it, step; rank_it != rank_range.end() && step < steps + 1; ++rank_it, step++)
    {
        if (step == 1)
        {
            CheckPawnCaptures(
                boardState,
                movesBoard,
                reactionBoard,
                actualPosition,
                movedChessMan,
                file,
                *rank_it,
                fileRange
            );
            CheckPawnCaptures(
                boardState,
                movesBoard,
                reactionBoard,
                actualPosition,
                movedChessMan,
                file,
                *rank_it,
                inverted_fileRange
            );
        }

        possiblePosition = ConvertFileAndRankToPosition(file, *rank_it);
        if (LookForPawnPossibleMoves(
            boardState,
            movesBoard,
            possiblePosition,
            actualPosition
        ))
            break;
    }
}
