#include "KingMoves.h"

KingMoves::KingMoves() : UpdateAttributes()
{
}

KingMoves::~KingMoves()
{
}

void KingMoves::CheckKingStraightMovesAndUpdateReactionBoard(
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
    int i(1);
	int fileIndex(file_range.find(file));
	auto file_it = file_range.begin() + fileIndex + 1;
	for (file_it, i; file_it != file_range.end() && i < 2; file_it++, i++)
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

	int j(1);
	int rankIndex(rank_range.find(rank));
	auto rank_it = rank_range.begin() + rankIndex + 1;
    for (rank_it, j; rank_it != rank_range.end() && j < 2; rank_it++, j++)
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

void KingMoves::CheckKingDiagonalMovesAndUpdateReactionBoard(
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
	int step(1);
	int fileIndex(file_range.find(file));
	int rankIndex(rank_range.find(rank));
	auto file_it = file_range.begin() + fileIndex + 1;
	auto rank_it = rank_range.begin() + rankIndex + 1;

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

void KingMoves::KingPossibleMoves(
	std::map<string, ChessMan> const boardState,
	std::map<string, std::list<string>>& movesBoard,
	std::map<string, std::list<ChessMan>>& reactionBoard,
	string const actualPosition,
	ChessMan const movedChessMan,
	char const file,
	char const rank
)
{
	CheckKingStraightMovesAndUpdateReactionBoard(
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
	CheckKingStraightMovesAndUpdateReactionBoard(
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

	std::list<string> file_range({ fileRange, inverted_fileRange });
	std::list<string> rank_range({ rankRange, inverted_rankRange });

	for (auto file_range_it = file_range.begin(); file_range_it != file_range.end(); file_range_it++)
	{
		for (auto rank_range_it = rank_range.begin(); rank_range_it != rank_range.end(); rank_range_it++)
		{
			CheckKingDiagonalMovesAndUpdateReactionBoard(
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
