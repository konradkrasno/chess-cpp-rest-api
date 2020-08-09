#include "KnightMoves.h"

KnightMoves::KnightMoves() : UpdateAttributes()
{
}

KnightMoves::~KnightMoves()
{
}

void KnightMoves::CheckKnightMovesAndUpdateReactionBoard(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string const actualPosition,
    ChessMan const movedChessMan,
    char const file,
    char const rank,
    string const file_range,
    string const rank_range,
	int const addFileStep,
	int const addRankStep
)
{
	int step(1);
	int fileIndex(file_range.find(file));
	int rankIndex(rank_range.find(rank));

	if (fileIndex + 1 < file_range.size() && rankIndex + 1 < rank_range.size())
	{
		auto file_it = file_range.begin() + fileIndex + 1 + addFileStep;
		auto rank_it = rank_range.begin() + rankIndex + 1 + addRankStep;
		for (file_it, rank_it, step;
			file_it != file_range.end() && rank_it != rank_range.end() && step < 2;
			file_it++, rank_it++, step++)
		{
			string possiblePosition(ConvertFileAndRankToPosition(*file_it, *rank_it));

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
}

void KnightMoves::KnightPossibleMoves(
    std::map<string, ChessMan> const boardState,
    std::map<string, std::list<string>>& movesBoard,
    std::map<string, std::list<ChessMan>>& reactionBoard,
    string const actualPosition,
    ChessMan const movedChessMan,
    char const file,
    char const rank
)
{
	std::list<string> file_range({ fileRange, inverted_fileRange });
	std::list<string> rank_range({ rankRange, inverted_rankRange });

	for (auto file_range_it = file_range.begin(); file_range_it != file_range.end(); file_range_it++)
	{
		for (auto rank_range_it = rank_range.begin(); rank_range_it != rank_range.end(); rank_range_it++)
		{
			CheckKnightMovesAndUpdateReactionBoard(
				boardState,
				movesBoard,
				reactionBoard,
				actualPosition,
				movedChessMan,
				file,
				rank,
				*file_range_it,
				*rank_range_it,
				0,
				1
			);
			CheckKnightMovesAndUpdateReactionBoard(
				boardState,
				movesBoard,
				reactionBoard,
				actualPosition,
				movedChessMan,
				file,
				rank,
				*file_range_it,
				*rank_range_it,
				1,
				0
			);
		}
	}
}
