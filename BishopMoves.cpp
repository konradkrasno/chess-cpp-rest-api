#include "BishopMoves.h"

BishopMoves::BishopMoves() : UpdateAttributes()
{
}

BishopMoves::~BishopMoves()
{
}

void BishopMoves::CheckBishopMovesAndUpdateReactionBoard(
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
	int rankIndex(rank_range.find(rank));
	auto file_it = file_range.begin() + fileIndex + 1;
	auto rank_it = rank_range.begin() + rankIndex + 1;

	for (file_it, rank_it;
		 file_it != file_range.end() && rank_it != rank_range.end();
		 file_it++, rank_it++)
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

void BishopMoves::BishopPossibleMoves(
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
			CheckBishopMovesAndUpdateReactionBoard(
				boardState,
				movesBoard,
				reactionBoard,
				actualPosition,
				movedChessMan,
				file,
				rank,
				*file_range_it,
				*rank_range_it
			);
		}
	}
}
