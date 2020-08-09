#include <iostream>
using std::cout;
using std::endl;

#include "BoardAttributes.h"

BoardAttributes::BoardAttributes()
{
    kingsPositions = InitialKingsPositions();
    boardState = StartingBoard();
    movesBoard = EmptyMovesBoard();
    reactionBoard = EmptyReactionBoard();
}

BoardAttributes::~BoardAttributes()
{
}

std::map<char, string> BoardAttributes::InitialKingsPositions()
{
    std::map <char, string> kingsPositions;
    kingsPositions.insert(std::pair<char, string>('w', "e1"));
    kingsPositions.insert(std::pair<char, string>('b', "e8"));
    return kingsPositions;
}

std::map<string, ChessMan> BoardAttributes::StartingBoard()
{
    // This is map object which assign ChessMan on every position on board.
    // map < Key, Value >
    // Key - position on board
    // Value - ChessMan on particular position

    std::map<string, ChessMan> mapping;

    mapping.insert(std::pair<string, ChessMan>("a1", ChessMan(ChessManType::Rook, 'w', "a1")));
    mapping.insert(std::pair<string, ChessMan>("b1", ChessMan(ChessManType::Knight, 'w', "b1")));
    mapping.insert(std::pair<string, ChessMan>("c1", ChessMan(ChessManType::Bishop, 'w', "c1")));
    mapping.insert(std::pair<string, ChessMan>("d1", ChessMan(ChessManType::Queen, 'w', "d1")));
    mapping.insert(std::pair<string, ChessMan>("e1", ChessMan(ChessManType::King, 'w', "e1")));    
    mapping.insert(std::pair<string, ChessMan>("f1", ChessMan(ChessManType::Bishop, 'w', "f1")));
    mapping.insert(std::pair<string, ChessMan>("g1", ChessMan(ChessManType::Knight, 'w', "g1")));
    mapping.insert(std::pair<string, ChessMan>("h1", ChessMan(ChessManType::Rook, 'w', "h1")));
    mapping.insert(std::pair<string, ChessMan>("a2", ChessMan(ChessManType::Pawn, 'w', "a2")));
    mapping.insert(std::pair<string, ChessMan>("b2", ChessMan(ChessManType::Pawn, 'w', "b2")));
    mapping.insert(std::pair<string, ChessMan>("c2", ChessMan(ChessManType::Pawn, 'w', "c2")));
    mapping.insert(std::pair<string, ChessMan>("d2", ChessMan(ChessManType::Pawn, 'w', "d2")));
    mapping.insert(std::pair<string, ChessMan>("e2", ChessMan(ChessManType::Pawn, 'w', "e2")));
    mapping.insert(std::pair<string, ChessMan>("f2", ChessMan(ChessManType::Pawn, 'w', "f2")));
    mapping.insert(std::pair<string, ChessMan>("g2", ChessMan(ChessManType::Pawn, 'w', "g2")));
    mapping.insert(std::pair<string, ChessMan>("h2", ChessMan(ChessManType::Pawn, 'w', "h2")));

    mapping.insert(std::pair<string, ChessMan>("a8", ChessMan(ChessManType::Rook, 'b', "a8")));
    mapping.insert(std::pair<string, ChessMan>("b8", ChessMan(ChessManType::Knight, 'b', "b8")));
    mapping.insert(std::pair<string, ChessMan>("c8", ChessMan(ChessManType::Bishop, 'b', "c8")));
    mapping.insert(std::pair<string, ChessMan>("d8", ChessMan(ChessManType::Queen, 'b', "d8")));
    mapping.insert(std::pair<string, ChessMan>("e8", ChessMan(ChessManType::King, 'b', "e8")));
    mapping.insert(std::pair<string, ChessMan>("f8", ChessMan(ChessManType::Bishop, 'b', "f8")));
    mapping.insert(std::pair<string, ChessMan>("g8", ChessMan(ChessManType::Knight, 'b', "g8")));
    mapping.insert(std::pair<string, ChessMan>("h8", ChessMan(ChessManType::Rook, 'b', "h8")));
    mapping.insert(std::pair<string, ChessMan>("a7", ChessMan(ChessManType::Pawn, 'b', "a7")));
    mapping.insert(std::pair<string, ChessMan>("b7", ChessMan(ChessManType::Pawn, 'b', "b7")));
    mapping.insert(std::pair<string, ChessMan>("c7", ChessMan(ChessManType::Pawn, 'b', "c7")));
    mapping.insert(std::pair<string, ChessMan>("d7", ChessMan(ChessManType::Pawn, 'b', "d7")));
    mapping.insert(std::pair<string, ChessMan>("e7", ChessMan(ChessManType::Pawn, 'b', "e7")));
    mapping.insert(std::pair<string, ChessMan>("f7", ChessMan(ChessManType::Pawn, 'b', "f7")));
    mapping.insert(std::pair<string, ChessMan>("g7", ChessMan(ChessManType::Pawn, 'b', "g7")));
    mapping.insert(std::pair<string, ChessMan>("h7", ChessMan(ChessManType::Pawn, 'b', "h7")));

    string emptyRankRange = "6543";
    for (char const& file : fileRange)
    {
        for (char const& rank : emptyRankRange)
        {
            string position(ConvertFileAndRankToPosition(file, rank));
            mapping.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
        }
    }
    return mapping;
}

std::map<string, std::list<string>> BoardAttributes::EmptyMovesBoard()
{
    // This is map object that contains lists of possible moves from particular position.
    // map < Key, Value >
    // Key - position on board
    // Value - list of positions which ChessMan from particular position can move

    std::map<string, std::list<string>> movesBoard;
    std::list<string> fields;

    for (char const& file : fileRange)
    {
        for (char const& rank : rankRange)
        {
            string position(ConvertFileAndRankToPosition(file, rank));
            movesBoard.insert(std::pair<string, std::list<string>>(position, fields));
        }
    }
    return movesBoard;
}

std::map<string, std::list<ChessMan>> BoardAttributes::EmptyReactionBoard()
{
    // This is map object that contains lists of ChessMan which can move to particular position.
    // map < Key, Value >
    // Key - position on board
    // Value - list of ChessMan which can move to position

    std::map<string, std::list<ChessMan>> reactionBoard;
    std::list<ChessMan> fields;

    for (char const& file : fileRange)
    {
        for (char const& rank : rankRange)
        {
            string position(ConvertFileAndRankToPosition(file, rank));
            reactionBoard.insert(std::pair<string, std::list<ChessMan>>(position, fields));
        }
    }
    return reactionBoard;
}
