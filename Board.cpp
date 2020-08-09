#include <iostream>
using std::cout;
using std::endl;

#include "Board.h"

Board::Board() : Move()
{
}

Board::~Board()
{
}

void Board::_DrawMiddle(LineType const lineType, char file, string chessManSymbol) const
{
    switch (lineType)
    {
    case LineType::FileHeader:
        cout << "  " << file << "   ";
        break;
    case LineType::TopHorizontalLine:
        cout << " _____";
        break;
    case LineType::VerticalLines:
        cout << "|" << "     ";
        break;
    case LineType::ChessManPlace:
        cout << "|" << "  " << chessManSymbol << "  ";
        break;
    case LineType::VerticalAndHorizontalLines:
        cout << "|" << "_____";
        break;
    default:
        break;
    }
}

void Board::_DrawEndBegin(LineEndBegin const lineEndBegin, char rank) const
{
    switch (lineEndBegin)
    {
    case LineEndBegin::TopLine:
        cout << endl;
        cout << "   ";
        break;
    case LineEndBegin::RankHeader:
        cout << "|" << endl;
        cout << " " << rank << " ";
        break;
    case LineEndBegin::InnerLine:
        cout << "|" << endl;
        cout << "   ";
        break;
    default:
        break;
    }
}

void Board::_DrawEntireNonPositionLine(LineType const lineType, LineEndBegin const lineEndBegin, string fileRange, char rank) const
{
    for (char const& file : fileRange)
    {
        Board::_DrawMiddle(lineType, file);
    }
    Board::_DrawEndBegin(lineEndBegin, rank);
}

void Board::_DrawEntirePositionLine(string fileRange, char rank) const
{
    for (char const& file : fileRange)
    {
        string chessManOnCurrentPositionSymbol(FindChessManOnBoard(file, rank).GetSymbol());
        if (chessManOnCurrentPositionSymbol != "none")
        {
            Board::_DrawMiddle(LineType::ChessManPlace, 0, chessManOnCurrentPositionSymbol);
        }
        else
        {
            Board::_DrawMiddle(LineType::VerticalLines);
        }
    }
    Board::_DrawEndBegin(LineEndBegin::InnerLine);
}

void Board::DrawBoard(char const playerColor, bool const invertTable) const
{
    string rank_range;
    if (invertTable)
    {
        if (playerColor == 'w') rank_range = rankRange;
        else rank_range = inverted_rankRange;
    }
    else
        rank_range = rankRange;

    cout << "    ";
    Board::_DrawEntireNonPositionLine(LineType::FileHeader, LineEndBegin::TopLine, fileRange);
    Board::_DrawEntireNonPositionLine(LineType::TopHorizontalLine, LineEndBegin::TopLine, fileRange);

    for (char const& rank : rank_range)
    {
        Board::_DrawEntireNonPositionLine(LineType::VerticalLines, LineEndBegin::RankHeader, fileRange, rank);
        Board::_DrawEntirePositionLine(fileRange, rank);
        Board::_DrawEntireNonPositionLine(LineType::VerticalAndHorizontalLines, LineEndBegin::InnerLine, fileRange);
    }
    cout << endl;
}

ChessMan Board::FindChessManOnBoard(char const file, char const rank) const
{
    string position(ConvertFileAndRankToPosition(file, rank));
    return boardAttributes.boardState.at(position);
}

void Board::CalculateMovesBoardAndReactionBoard()
{
    boardAttributes.movesBoard = boardAttributes.EmptyMovesBoard();
    boardAttributes.reactionBoard = boardAttributes.EmptyReactionBoard();

    for (char const& file : fileRange)
    {
        for (char const& rank : rankRange)
        {
            string position(ConvertFileAndRankToPosition(file, rank));
            ChessManPossibleMoves(position);
        }
    }
}

void Board::CalculateMovesBoardAndReactionBoardWithNeutralKings()
{
    string whiteKingPosition(boardAttributes.kingsPositions.at('w'));
    ChessMan& whiteKingField(boardAttributes.boardState.at(whiteKingPosition));
    ChessMan const copyWhiteKing(whiteKingField);

    string blackKingPosition(boardAttributes.kingsPositions.at('b'));
    ChessMan& blackKingField(boardAttributes.boardState.at(blackKingPosition));
    ChessMan const copyBlackKing(blackKingField);

    whiteKingField = ChessMan(ChessManType::None, 0);
    blackKingField = ChessMan(ChessManType::None, 0);

    CalculateMovesBoardAndReactionBoard();

    whiteKingField = copyWhiteKing;
    blackKingField = copyBlackKing;

    KingPossibleMoves(
        boardAttributes.boardState,
        boardAttributes.movesBoard,
        boardAttributes.reactionBoard,
        whiteKingPosition,
        whiteKingField,
        whiteKingPosition[0],
        whiteKingPosition[1]
    );
    KingPossibleMoves(
        boardAttributes.boardState,
        boardAttributes.movesBoard,
        boardAttributes.reactionBoard,
        blackKingPosition,
        blackKingField,
        blackKingPosition[0],
        blackKingPosition[1]
    );
}

bool Board::Check(char const kingColor, string const kingPosition)
{
    std::list<ChessMan> kingFieldReactions(boardAttributes.reactionBoard.at(kingPosition));
    for (std::list<ChessMan>::iterator kingReactions_it = kingFieldReactions.begin(); kingReactions_it != kingFieldReactions.end(); kingReactions_it++)
    {
        char reactingChessManColor(kingReactions_it->GetColor());
        if (reactingChessManColor != kingColor)
        {
            return true;
        }
    }
    return false;
}

bool Board::CheckMate(char const kingColor)
{
    bool kingIsCheck(false);
    bool allKingMovesIsChecked(true);
    bool checkingChessManNotCaptured(true);

    string kingPosition(boardAttributes.kingsPositions.at(kingColor));
    if (Check(kingColor, kingPosition))
    {
        kingIsCheck = true;
    }

    if (!kingIsCheck) return false;

    std::list<string> kingMoves(boardAttributes.movesBoard.at(kingPosition));
    for (std::list<string>::iterator kingMoves_it = kingMoves.begin(); kingMoves_it != kingMoves.end(); kingMoves_it++)
    {
        if (!Check(kingColor, *kingMoves_it))
        {
            allKingMovesIsChecked = false;
            break;
        }
    }

    if (!allKingMovesIsChecked) return false;

    int count(0);
    std::list<ChessMan> reactingChessMen(boardAttributes.reactionBoard.at(kingPosition));
    for (std::list<ChessMan>::iterator enemy_it = reactingChessMen.begin(); enemy_it != reactingChessMen.end(); enemy_it++)
    {
        if (enemy_it->GetColor() != kingColor)
        {
            count += 1;

            string enemyPosition(enemy_it->GetPosition());
            std::list<ChessMan> defenders(boardAttributes.reactionBoard.at(enemyPosition));
            for (std::list<ChessMan>::iterator defender_it = defenders.begin();
                defender_it != defenders.end();
                defender_it++)
            {
                if (defender_it->GetColor() == kingColor && defender_it->GetType() != ChessManType::King)
                {
                    ChessMan& defender(boardAttributes.boardState.at(defender_it->GetPosition()));
                    ChessMan const copy_defender(defender);
                    defender = ChessMan(ChessManType::None, 0);

                    ChessMan& enemy(boardAttributes.boardState.at(enemy_it->GetPosition()));
                    ChessMan& copy_enemy(enemy);
                    enemy = defender;

                    CalculateMovesBoardAndReactionBoardWithNeutralKings();

                    if (!Check(kingColor, kingPosition))
                        checkingChessManNotCaptured = false;

                    defender = copy_defender;
                    enemy = copy_enemy;
                }
            }
        }
    }

    if (count > 1)
    {
        checkingChessManNotCaptured = true;
    }

    if (!checkingChessManNotCaptured) return false;

    return true;
}

bool Board::MakeMove(char const playerColor, string const actualPosition, string const newPosition, string test_input)
{
    CalculateMovesBoardAndReactionBoard();
    ChessMan& actualPositionChessMan(boardAttributes.boardState.at(actualPosition));
    ChessMan const copy_actualPositionChessMan(actualPositionChessMan);
    ChessMan& newPositionChessMan(boardAttributes.boardState.at(newPosition));
    ChessMan const copy_newPositionChessMan(newPositionChessMan);

    string& kingPosition(boardAttributes.kingsPositions.at(playerColor));

    if (copy_actualPositionChessMan.GetColor() == playerColor)
    {
        std::list<string> allowedMoves(boardAttributes.movesBoard.at(actualPosition));
        for (std::list<string>::iterator moves_itr = allowedMoves.begin(); moves_itr != allowedMoves.end(); moves_itr++)
        {
            if (newPosition == *moves_itr)
            {
                if (copy_actualPositionChessMan.GetType() == ChessManType::Pawn)
                {
                    if (newPosition[1] == '1' || newPosition[1] == '8')
                    {
                        return PawnOnEndLine(
                            playerColor,
                            actualPositionChessMan,
                            copy_actualPositionChessMan,
                            newPositionChessMan,
                            newPosition,
                            kingPosition,
                            test_input
                        );
                    }
                }

                actualPositionChessMan = ChessMan(ChessManType::None, 0);
                newPositionChessMan = copy_actualPositionChessMan;
                newPositionChessMan.ChangePosition(newPosition);

                if (copy_actualPositionChessMan.GetType() == ChessManType::King) kingPosition = newPosition;

                CalculateMovesBoardAndReactionBoardWithNeutralKings();
                if (Check(playerColor, kingPosition))
                {
                    cout << "Move is not allowed. The King is checked!" << endl;
                    actualPositionChessMan = copy_actualPositionChessMan;
                    newPositionChessMan = copy_newPositionChessMan;
                    if (copy_actualPositionChessMan.GetType() == ChessManType::King) kingPosition = actualPosition;

                    return false;
                }
                newPositionChessMan.ChangeFirstMove();

                return true;
            }
        }
    }

    cout << "Move is not allowed." << endl;
    return false;
}

int Board::GetInputForPawnOnEndLine(char const playerColor, string const test_input)
{
    cout << "Your Pawn achieved end line! For what chessman would you like to change your Pawn?" << endl;
    cout << "Print:" << endl;
    cout << "1 for Queen" << endl;
    cout << "2 for Rook" << endl;
    cout << "3 for Knight" << endl;
    cout << "4 for Bishop" << endl;

    string input;
    while (true)
    {
        if (test_input != "default") input = test_input;
        else std::cin >> input;

        if (input == "1") return 1;
        else if (input == "2") return 2;
        else if (input == "3") return 3;
        else if (input == "4") return 4;

        cout << "Wrong command. Try again" << endl;
    }
}

bool Board::PawnOnEndLine(
    char const playerColor,
    ChessMan& actualPositionChessMan,
    ChessMan const copy_actualPositionChessMan,
    ChessMan& newPositionChessMan,
    string const newPosition,
    string kingPosition,
    string const test_input
)
{
    int choice(GetInputForPawnOnEndLine(playerColor, test_input));

    actualPositionChessMan = ChessMan(ChessManType::None, 0);
    switch (choice)
    {
    case 1:
        newPositionChessMan = ChessMan(ChessManType::Queen, playerColor, newPosition);
        break;
    case 2:
        newPositionChessMan = ChessMan(ChessManType::Rook, playerColor, newPosition);
        break;
    case 3:
        newPositionChessMan = ChessMan(ChessManType::Knight, playerColor, newPosition);
        break;
    case 4:
        newPositionChessMan = ChessMan(ChessManType::Bishop, playerColor, newPosition);
        break;
    default:
        break;
    }
    newPositionChessMan.ChangePosition(newPosition);

    CalculateMovesBoardAndReactionBoardWithNeutralKings();
    if (Check(playerColor, kingPosition))
    {
        cout << "Move is not allowed. The King is checked!" << endl;
        actualPositionChessMan = copy_actualPositionChessMan;
        newPositionChessMan = ChessMan(ChessManType::None, 0);

        return false;
    }
    return true;
}

bool Board::NotFirstMove(char const file, char const rank)
{
    string chessManPosition(ConvertFileAndRankToPosition(file, rank));
    ChessMan chessManField(boardAttributes.boardState.at(chessManPosition));
    if (chessManField.CheckFirstMove() != true) return true;
    return false;
}

bool Board::NotEmpty(char const file, char const rank)
{
    string chessManPosition(ConvertFileAndRankToPosition(file, rank));
    ChessMan kingField(boardAttributes.boardState.at(chessManPosition));
    if (kingField.GetType() != ChessManType::None) return true;
    return false;
}

void Board::LookForCastling(char const playerColor, char const file, char const rank, string const file_range, int& cast, char& rookFileForCastling)
{
    if (NotFirstMove(file, rank))
    {
        cout << "Rook on " << file << rank << " was moved" << endl;
        cast = 0;
    }
    else
    {

        for (auto file_it = file_range.begin(); file_it != file_range.end(); file_it++)
        {
            if (Check(playerColor, ConvertFileAndRankToPosition(*file_it, rank)))
            {
                cout << "Move is not allowed. The King is checked!" << endl;
                cast = 0;
                break;
            }
            if (NotEmpty(*file_it, rank))
            {
                cast = 0;
                break;
            }
        }
        if (cast) rookFileForCastling = file;
    }
}

int Board::FindCastlings(char const playerColor, char& rookFileForCastling, char const castlingRank)
{
    int castlingA(1);
    int castlingH(1);

    char rook_fileA('a');
    char rook_fileH('h');
    char king_file('e');
    string empty_files_rookA("bcd");
    string empty_files_rookH("fg");

    CalculateMovesBoardAndReactionBoardWithNeutralKings();

    if (NotFirstMove(king_file, castlingRank))
    {
        cout << "King was moved" << endl;
        return 0;
    }

    if (Check(playerColor, ConvertFileAndRankToPosition(king_file, castlingRank)))
    {
        cout << "Move is not allowed. The King is checked!" << endl;
        return 0;
    }

    LookForCastling(playerColor, rook_fileA, castlingRank, empty_files_rookA, castlingA, rookFileForCastling);
    LookForCastling(playerColor, rook_fileH, castlingRank, empty_files_rookH, castlingH, rookFileForCastling);
    
    int castling(castlingA + castlingH);
    if (castling == 2) rookFileForCastling = 0;

    return castling;
}

void Board::MakeCastling(char const playerColor, char const rookFile, char const castlingRank)
{
    string file_range;
    if (rookFile == 'a') file_range = fileRange;
    else file_range = inverted_fileRange;

    string actualRookPosition(ConvertFileAndRankToPosition(rookFile, castlingRank));
    string actualKingPosition(ConvertFileAndRankToPosition('e', castlingRank));

    char const newRookFile(file_range[2]);
    char const newKingFile(file_range[1]);
    string newRookPosition(ConvertFileAndRankToPosition(newRookFile, castlingRank));
    string newKingPosition(ConvertFileAndRankToPosition(newKingFile, castlingRank));

    ChessMan& actualRookPositionField(boardAttributes.boardState.at(actualRookPosition));
    ChessMan& newRookPositionField(boardAttributes.boardState.at(newRookPosition));
    newRookPositionField = actualRookPositionField;
    newRookPositionField.ChangePosition(newRookPosition);
    newRookPositionField.ChangeFirstMove();
    actualRookPositionField = ChessMan(ChessManType::None, 0);

    ChessMan& actualKingPositionField(boardAttributes.boardState.at(actualKingPosition));
    ChessMan& newKingPositionField(boardAttributes.boardState.at(newKingPosition));
    newKingPositionField = actualKingPositionField;
    newKingPositionField.ChangePosition(newKingPosition);
    newKingPositionField.ChangeFirstMove();
    boardAttributes.kingsPositions.at(playerColor) = newKingPosition;
    actualKingPositionField = ChessMan(ChessManType::None, 0);

    CalculateMovesBoardAndReactionBoardWithNeutralKings();
}
