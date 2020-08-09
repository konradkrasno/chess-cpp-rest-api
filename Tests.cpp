#include <iostream>
using std::cout;
using std::endl;
#define BOOST_TEST_MODULE testChess
#include <boost/test/included/unit_test.hpp>
#include "Move.h"
#include "ChessMan.h"
#include "Gameplay.h"


struct FakeBoardAttributesFixture
{
    FakeBoardAttributesFixture()
    {
        std::map<string, ChessMan> fakeBoardState;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                fakeBoardState.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
            }
        }
        fakeBoardState.at("b2") = ChessMan(ChessManType::Rook, 'w', "b2");
        fakeBoardState.at("g6") = ChessMan(ChessManType::Rook, 'w', "g6");
        fakeBoardState.at("e2") = ChessMan(ChessManType::Knight, 'w', "e2");
        fakeBoardState.at("b8") = ChessMan(ChessManType::Knight, 'w', "b8");
        fakeBoardState.at("d2") = ChessMan(ChessManType::Bishop, 'w', "d2");
        fakeBoardState.at("d1") = ChessMan(ChessManType::Queen, 'w', "d1");
        fakeBoardState.at("e1") = ChessMan(ChessManType::King, 'w', "e1");
        fakeBoardState.at("a6") = ChessMan(ChessManType::Pawn, 'w', "a6");
        fakeBoardState.at("g4") = ChessMan(ChessManType::Pawn, 'w', "g4");
        fakeBoardState.at("e4") = ChessMan(ChessManType::Pawn, 'w', "e4");

        fakeBoardState.at("b6") = ChessMan(ChessManType::Pawn, 'b', "b6");
        fakeBoardState.at("e5") = ChessMan(ChessManType::Pawn, 'b', "e5");
        fakeBoardState.at("d5") = ChessMan(ChessManType::Pawn, 'b', "d5");
        fakeBoardState.at("f4") = ChessMan(ChessManType::Pawn, 'b', "f4");
        fakeBoardState.at("h7") = ChessMan(ChessManType::Pawn, 'b', "h7");

        std::map<string, std::list<string>> fakeMovesBoard;
        std::list<string> emptyStringList;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                fakeMovesBoard.insert(std::pair<string, std::list<string>>(position, emptyStringList));
            }
        }

        std::map<string, std::list<ChessMan>> fakeReactionBoard;
        std::list<ChessMan> emptyChessManList;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                fakeReactionBoard.insert(std::pair<string, std::list<ChessMan>>(position, emptyChessManList));
            }
        }

        BoardAttributes fakeBoardAttributes;
        fakeBoardAttributes.boardState = fakeBoardState;
        fakeBoardAttributes.movesBoard = fakeMovesBoard;
        fakeBoardAttributes.reactionBoard = fakeReactionBoard;

        Move fakeMove;
        fakeMove.boardAttributes = fakeBoardAttributes;
        move = new Move;
        *move = fakeMove;

        Board fakeBoard;
        fakeBoard.boardAttributes = fakeBoardAttributes;
        board = new Board;
        *board = fakeBoard;

        Gameplay fakeGameplay;
        fakeGameplay.board = *board;
        gameplay = new Gameplay;
        *gameplay = fakeGameplay;
    }
    ~FakeBoardAttributesFixture()
    {
        delete move;
        delete board;
        delete gameplay;
    }
    Move* move;
    Board* board;
    Gameplay* gameplay;
};

struct FakeBoardFixture
{
    FakeBoardFixture()
    {
        Board board;
        fakeBoard = new Board;
        *fakeBoard = board;

        Gameplay gameplay;
        gameplay.board = *fakeBoard;
        fakeGameplay = new Gameplay;
        *fakeGameplay = gameplay;

    }
    ~FakeBoardFixture()
    {
        delete fakeBoard;
        delete fakeGameplay;
    }
    Board* fakeBoard;
    Gameplay* fakeGameplay;
};

struct EmptyBoardFixture
{
    EmptyBoardFixture()
    {
        std::map<string, ChessMan> emptyBoardState;
        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                emptyBoardState.insert(std::pair<string, ChessMan>(position, ChessMan(ChessManType::None, 0)));
            }
        }

        Board board;
        board.boardAttributes.boardState = emptyBoardState;
        emptyBoard = new Board;
        *emptyBoard = board;

        Gameplay gameplay;
        gameplay.board = *emptyBoard;
        emptyGameplay = new Gameplay;
        *emptyGameplay = gameplay;

    }
    ~EmptyBoardFixture()
    {
        delete emptyBoard;
        delete emptyGameplay;
    }
    Board* emptyBoard;
    Gameplay* emptyGameplay;
};



BOOST_AUTO_TEST_SUITE(MoveSuite)
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForRook, FakeBoardAttributesFixture)
{
    string testPosition("b2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "c2", "b1", "a2", "b3", "b4", "b5", "b6" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKnight, FakeBoardAttributesFixture)
{
    string testPosition("e2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "g1", "f4", "g3", "c1", "d4", "c3" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKnightOnEdge, FakeBoardAttributesFixture)
{
    string testPosition("b8");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "c6", "d7" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForBishop, FakeBoardAttributesFixture)
{
    string testPosition("d2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "e3", "f4", "c1", "c3", "b4", "a5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForQueen, FakeBoardAttributesFixture)
{
    string testPosition("d1");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "c1", "b1", "a1", "c2", "b3", "a4" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKingVariant1, FakeBoardAttributesFixture)
{
    string testPosition("e1");
    move->boardAttributes.boardState.at("d2") = ChessMan(ChessManType::Queen, 'b', "d2");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;
    
    std::list<string> expectedMoves({ "f1", "f2", "d2" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForKingVariant2, EmptyBoardFixture)
{
    string testPosition("e4");

    emptyBoard->boardAttributes.boardState.at("e4") = ChessMan(ChessManType::King, 'w', "e4");

    emptyBoard->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(emptyBoard->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "f4", "e3", "d4", "e5", "f3", "f5", "d3", "d5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}


BOOST_FIXTURE_TEST_CASE(testPossibleMovesForPawn, FakeBoardAttributesFixture)
{
    string testPosition("g4");
    move->boardAttributes.boardState.at("g4").ChangeFirstMove();
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "g5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForPawnWhenBlocked, FakeBoardAttributesFixture)
{
    string testPosition("e4");
    move->boardAttributes.boardState.at("g4").ChangeFirstMove();
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "d5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testPossibleMovesForPawnOnFirstLine, FakeBoardAttributesFixture)
{
    string testPosition("h7");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    cout << "moves: " << endl;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) cout << *it << endl;

    std::list<string> expectedMoves({ "g6", "h6", "h5" });
    BOOST_CHECK(possibleMoves == expectedMoves);
}

BOOST_FIXTURE_TEST_CASE(testPossibleMovesForEmptyField, FakeBoardAttributesFixture)
{
    string testPosition("a8");
    move->ChessManPossibleMoves(testPosition);

    std::list<string> possibleMoves(move->boardAttributes.movesBoard.at(testPosition));
    std::list<string> expectedMoves({});
    BOOST_CHECK(possibleMoves == expectedMoves);
}
BOOST_FIXTURE_TEST_CASE(testWorkingUpdateReactionBoardForRook, FakeBoardAttributesFixture)
{
    move->ChessManPossibleMoves("b2");

    std::list<ChessMan> fields;
    fields = move->boardAttributes.reactionBoard.at("c2");
    std::list<ChessMan>::iterator it = fields.begin();
    ChessMan insertedChessMan(*it);
    ChessMan expectedChessMan(ChessManType::Rook, 'w', "b2");
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testWorkingUpdateReactionBoardForPawn, FakeBoardAttributesFixture)
{
    move->ChessManPossibleMoves("h7");

    std::list<ChessMan> fields;
    fields = move->boardAttributes.reactionBoard.at("g6");
    std::list<ChessMan>::iterator it = fields.begin();
    ChessMan insertedChessMan(*it);
    ChessMan expectedChessMan(ChessManType::Pawn, 'b', "h7");
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ChessManSuite)
BOOST_AUTO_TEST_CASE(testlEqualOperator)
{
    ChessMan whiteRook1(ChessManType::Rook, 'w', "c2");
    ChessMan whiteRook2(ChessManType::Rook, 'w', "c2");
    BOOST_CHECK(whiteRook1 == whiteRook2);
}
BOOST_AUTO_TEST_CASE(testlNotEqualOperatorForSymbol)
{
    ChessMan whiteRook(ChessManType::Rook, 'w', "c2");
    ChessMan whiteKnight(ChessManType::Knight, 'w', "c2");
    BOOST_CHECK(whiteRook != whiteKnight);
}
BOOST_AUTO_TEST_CASE(testlNotEqualOperatorForPosition)
{
    ChessMan whiteRook1(ChessManType::Rook, 'w', "c2");
    ChessMan whiteRook2(ChessManType::Rook, 'w', "g3");
    BOOST_CHECK(whiteRook1 != whiteRook2);
}
BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(BoardSuite)
BOOST_FIXTURE_TEST_CASE(testCalculateStateBoardAndReactionBoard, FakeBoardAttributesFixture)
{
    string testPosition1("b2");
    string testPosition2("g6");

    board->CalculateMovesBoardAndReactionBoard();
    board->CalculateMovesBoardAndReactionBoard();

    std::list<string> possibleMovesFromPosition1(board->boardAttributes.movesBoard.at(testPosition1));
    cout << "moves: " << endl;
    for (auto it = possibleMovesFromPosition1.begin(); it != possibleMovesFromPosition1.end(); it++) cout << *it << endl;
    std::list<string> expectedMovesFromPosition1({ "c2", "b1", "a2", "b3", "b4", "b5", "b6" });

    std::list<string> possibleMovesFromPosition2(board->boardAttributes.movesBoard.at(testPosition2));
    cout << "moves: " << endl;
    for (auto it = possibleMovesFromPosition2.begin(); it != possibleMovesFromPosition2.end(); it++) cout << *it << endl;
    std::list<string> expectedMovesFromPosition2({ "h6", "g5", "f6", "e6", "d6", "c6", "b6", "g7", "g8" });

    BOOST_CHECK(possibleMovesFromPosition1 == expectedMovesFromPosition1);
    BOOST_CHECK(possibleMovesFromPosition2 == expectedMovesFromPosition2);

    std::list<ChessMan> reactions;
    reactions = board->boardAttributes.reactionBoard.at("b6");
    std::list<ChessMan>::iterator reactions_it = reactions.begin();

    ChessMan expectedChessMan1(ChessManType::Rook, 'w', "b2");
    ChessMan insertedChessMan1(*reactions_it);
    BOOST_CHECK(insertedChessMan1 == expectedChessMan1);

    std::advance(reactions_it, 1);
    ChessMan expectedChessMan2(ChessManType::Rook, 'w', "g6");
    ChessMan insertedChessMan2(*reactions_it);
    BOOST_CHECK(insertedChessMan2 == expectedChessMan2);

    BOOST_CHECK(reactions.size() == 2);
}

BOOST_FIXTURE_TEST_CASE(testCheckWhenFalseWhenFieldHasNoReactions, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("a8");

    board->CalculateMovesBoardAndReactionBoardWithNeutralKings();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckWhenFalseWhenFieldHasReactions, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("e1");

    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'w', "h1");
    board->CalculateMovesBoardAndReactionBoardWithNeutralKings();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckWhenTrue, FakeBoardAttributesFixture)
{
    char kingColor('w');
    string kingPosition("e1");

    board->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::Rook, 'b', "h1");
    board->CalculateMovesBoardAndReactionBoardWithNeutralKings();

    bool check(board->Check(kingColor, kingPosition));
    BOOST_CHECK(check == true);
}

BOOST_FIXTURE_TEST_CASE(testMakeMoveToEmptyField, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "b4");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b4"));
    ChessMan expectedChessMan(ChessMan(ChessManType::Rook, 'w', "b4"));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testCapture, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "b6");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b6"));
    ChessMan expectedChessMan(ChessMan(ChessManType::Rook, 'w', "b6"));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveToNotEmptyField, FakeBoardAttributesFixture)
{
    board->MakeMove('w', "b2", "d2");
    ChessMan insertedChessManD2(board->boardAttributes.boardState.at("d2"));
    ChessMan expectedChessManD2(ChessMan(ChessManType::Bishop, 'w', "d2"));
    BOOST_CHECK(insertedChessManD2 == expectedChessManD2);
    ChessMan insertedChessManB2(board->boardAttributes.boardState.at("b2"));
    ChessMan expectedChessManB2(ChessMan(ChessManType::Rook, 'w', "b2"));
    BOOST_CHECK(insertedChessManB2 == expectedChessManB2);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByDifferentColor, FakeBoardAttributesFixture)
{
    board->MakeMove('b', "b2", "b4");
    ChessMan insertedChessMan(board->boardAttributes.boardState.at("b4"));
    ChessMan expectedChessMan(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessMan == expectedChessMan);
}

////////////////////////////
// MakeMove when Check tests
////////////////////////////
BOOST_FIXTURE_TEST_CASE(testMakeMoveByNotKingCauseCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("a1") = ChessMan(ChessManType::Rook, 'b', "a1");

    board->MakeMove('w', "d1", "b3");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("b3"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("d1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::Queen, 'w', "d1"));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByKingCauseCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("c5") = ChessMan(ChessManType::Bishop, 'b', "c5");

    board->MakeMove('w', "e1", "f2");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("f2"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("e1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::King, 'w', "e1"));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByNotKingWhenCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Bishop, 'b', "h4");

    board->MakeMove('w', "d1", "d3");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("d3"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("d1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::Queen, 'w', "d1"));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testEscapeByKingWhenCheck, FakeBoardAttributesFixture)
{
    board->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Bishop, 'b', "h4");

    board->MakeMove('w', "e1", "f1");
    ChessMan insertedChessManF2(board->boardAttributes.boardState.at("f1"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::King, 'w', "f1"));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(board->boardAttributes.boardState.at("e1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testCaptureByKingToAvoidCheck, EmptyBoardFixture)
{
    emptyBoard->boardAttributes.boardState.at("e1") = ChessMan(ChessManType::King, 'w', "e1");
    emptyBoard->boardAttributes.boardState.at("d2") = ChessMan(ChessManType::Pawn, 'w', "d2");
    emptyBoard->boardAttributes.boardState.at("f2") = ChessMan(ChessManType::Pawn, 'w', "f2");

    emptyBoard->boardAttributes.boardState.at("e2") = ChessMan(ChessManType::Queen, 'b', "e2");

    emptyBoard->MakeMove('w', "e1", "e2");
    ChessMan insertedChessManF2(emptyBoard->boardAttributes.boardState.at("e2"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::King, 'w', "e2"));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(emptyBoard->boardAttributes.boardState.at("e1"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testCaptureByKnightToAvoidCheck, EmptyBoardFixture)
{
    emptyBoard->boardAttributes.boardState.at("e1") = ChessMan(ChessManType::King, 'w', "e1");
    emptyBoard->boardAttributes.boardState.at("d2") = ChessMan(ChessManType::Pawn, 'w', "d2");
    emptyBoard->boardAttributes.boardState.at("f2") = ChessMan(ChessManType::Pawn, 'w', "f2");
    emptyBoard->boardAttributes.boardState.at("c3") = ChessMan(ChessManType::Knight, 'w', "c3");

    emptyBoard->boardAttributes.boardState.at("e2") = ChessMan(ChessManType::Queen, 'b', "e2");

    emptyBoard->MakeMove('w', "c3", "e2");
    ChessMan insertedChessManF2(emptyBoard->boardAttributes.boardState.at("e2"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Knight, 'w', "e2"));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(emptyBoard->boardAttributes.boardState.at("c3"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}


BOOST_FIXTURE_TEST_CASE(testMakeMoveByQueenToAvoidCheck, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("e7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("e4") = ChessMan(ChessManType::Queen, 'w', "e4");

    fakeBoard->MakeMove('b', "d8", "e7");
    ChessMan insertedChessManF2(fakeBoard->boardAttributes.boardState.at("e7"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Queen, 'b', "e7"));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(fakeBoard->boardAttributes.boardState.at("d8"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testMakeMoveByBishopToAvoidCheck, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("a4") = ChessMan(ChessManType::Bishop, 'w', "a4");

    fakeBoard->MakeMove('b', "c8", "d7");
    ChessMan insertedChessManF2(fakeBoard->boardAttributes.boardState.at("d7"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Bishop, 'b', "d7"));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(fakeBoard->boardAttributes.boardState.at("c8"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}
BOOST_FIXTURE_TEST_CASE(testCaptureByPawnToAvoidCheck, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b5") = ChessMan(ChessManType::Bishop, 'w', "b5");
    fakeBoard->boardAttributes.boardState.at("a7") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("a6") = ChessMan(ChessManType::Pawn, 'b', "a6");

    fakeBoard->MakeMove('b', "a6", "b5");
    ChessMan insertedChessManF2(fakeBoard->boardAttributes.boardState.at("b5"));
    ChessMan expectedChessManF2(ChessMan(ChessManType::Pawn, 'b', "b5"));
    BOOST_CHECK(insertedChessManF2 == expectedChessManF2);
    ChessMan insertedChessManF1(fakeBoard->boardAttributes.boardState.at("a6"));
    ChessMan expectedChessManF1(ChessMan(ChessManType::None, 0));
    BOOST_CHECK(insertedChessManF1 == expectedChessManF1);
}

///////////////////////////
// Castling tests for Board
///////////////////////////
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenCollision, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenRookIsMoved, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("a8").ChangeFirstMove();

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenKingIsMoved, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("e8").ChangeFirstMove();

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenOneCastlingWithRookA, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 1);
    BOOST_CHECK(rookFileForCastling == 'a');
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenOneCastlingWithRookH, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 1);
    BOOST_CHECK(rookFileForCastling == 'h');
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenTwoCastlings, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 2);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingWhenKingIsChecked, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b8") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("f6") = ChessMan(ChessManType::Knight, 'w', "f6");

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenCastlingFieldIsCheckedVariant1, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("g7") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("g5") = ChessMan(ChessManType::Rook, 'w', "g5");

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}
BOOST_FIXTURE_TEST_CASE(testFindCastlingsWhenCastlingFieldIsCheckedVariant2, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("g8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f8") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("f7") = ChessMan(ChessManType::None, 0);

    fakeBoard->boardAttributes.boardState.at("f5") = ChessMan(ChessManType::Rook, 'w', "f5");

    char rookFileForCastling(0);

    int castling(fakeBoard->FindCastlings('b', rookFileForCastling, '8'));

    BOOST_CHECK(castling == 0);
    BOOST_CHECK(rookFileForCastling == 0);
}

BOOST_FIXTURE_TEST_CASE(testMakeCastlingForRookOnFileA, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);

    fakeBoard->MakeCastling('w', 'a', '1');

    ChessMan insertedKing(fakeBoard->boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w', "b1"));
    ChessMan insertedRook(fakeBoard->boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w', "c1"));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testMakeCastlingForRookOnFileH, FakeBoardFixture)
{
    fakeBoard->boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeBoard->boardAttributes.boardState.at("g1") = ChessMan(ChessManType::None, 0);

    fakeBoard->MakeCastling('w', 'h', '1');

    ChessMan insertedKing(fakeBoard->boardAttributes.boardState.at("g1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w', "g1"));
    ChessMan insertedRook(fakeBoard->boardAttributes.boardState.at("f1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w', "f1"));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}

////////////////////////////
// CheckMate tests for Board
////////////////////////////
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant1, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w', "h1");
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";

    emptyBoard->boardAttributes.boardState.at("g2") = ChessMan(ChessManType::Queen, 'b', "g2");
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b', "e3");

    emptyBoard->CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyBoard->CheckMate(playerColor));
    
    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant2, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w', "h1");
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";
    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Rook, 'w', "a2");

    emptyBoard->boardAttributes.boardState.at("g2") = ChessMan(ChessManType::Queen, 'b', "g2");
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b', "e3");
    emptyBoard->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Rook, 'b', "h4");

    emptyBoard->CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant3, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Pawn, 'w', "a2");
    emptyBoard->boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Pawn, 'w', "b2");
    emptyBoard->boardAttributes.boardState.at("a1") = ChessMan(ChessManType::King, 'w', "a1");
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "a1";

    emptyBoard->boardAttributes.boardState.at("e1") = ChessMan(ChessManType::Rook, 'b', "e1");

    emptyBoard->CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant1, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w', "h1");
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";
    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Rook, 'w', "a2");

    emptyBoard->boardAttributes.boardState.at("g2") = ChessMan(ChessManType::Queen, 'b', "g2");
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b', "e3");

    emptyBoard->CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant2, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w', "h1");
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "h1";
    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Rook, 'w', "a2");

    emptyBoard->boardAttributes.boardState.at("h4") = ChessMan(ChessManType::Rook, 'b', "h4");
    emptyBoard->boardAttributes.boardState.at("e3") = ChessMan(ChessManType::Knight, 'b', "e3");

    emptyBoard->CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant3, EmptyBoardFixture)
{
    char playerColor('w');

    emptyBoard->boardAttributes.boardState.at("a2") = ChessMan(ChessManType::Pawn, 'w', "a2");
    emptyBoard->boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Pawn, 'w', "b2");
    emptyBoard->boardAttributes.boardState.at("a1") = ChessMan(ChessManType::King, 'w', "a1");
    emptyBoard->boardAttributes.kingsPositions.at(playerColor) = "a1";
    emptyBoard->boardAttributes.boardState.at("e4") = ChessMan(ChessManType::Rook, 'w', "e4");

    emptyBoard->boardAttributes.boardState.at("e1") = ChessMan(ChessManType::Rook, 'b', "e1");

    emptyBoard->CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyBoard->CheckMate(playerColor));

    BOOST_CHECK(checkMate == false);
}

/////////////////////////////
// Tests for Pawn on end line
/////////////////////////////
BOOST_FIXTURE_TEST_CASE(testPawnOnEndLineWhenQueenSelected, EmptyBoardFixture)
{
    emptyBoard->boardAttributes.boardState.at("d7") = ChessMan(ChessManType::Pawn, 'w', "d7");

    emptyBoard->MakeMove('w', "d7", "d8", "1");

    ChessMan insertedChessMan(emptyBoard->boardAttributes.boardState.at("d8"));
    ChessMan expectedChessMan(ChessMan(ChessManType::Queen, 'w', "d8"));

    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_FIXTURE_TEST_CASE(testPawnOnEndLineWhenRookSelected, EmptyBoardFixture)
{
    emptyBoard->boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Pawn, 'b', "b2");

    emptyBoard->MakeMove('b', "b2", "b1", "2");

    ChessMan insertedChessMan(emptyBoard->boardAttributes.boardState.at("b1"));
    ChessMan expectedChessMan(ChessMan(ChessManType::Rook, 'b', "b1"));

    BOOST_CHECK(insertedChessMan == expectedChessMan);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(GameplaySuite)
BOOST_AUTO_TEST_CASE(testValidateInputIfValid)
{
    string input("f3");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == true);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfToLong)
{
    string input("ewr");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfInverted)
{
    string input("4d");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfFileOutOfRange)
{
    string input("k4");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}
BOOST_AUTO_TEST_CASE(testValidateInputIfRankOutOfRange)
{
    string input("c9");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.ValidatePositionInput(input) == false);
}

BOOST_AUTO_TEST_CASE(testMakeLowercaseWithCoordinates)
{
    string input("D6");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.MakeLowercase(input) == "d6");
}
BOOST_AUTO_TEST_CASE(testMakeLowercaseWithString)
{
    string input("Draw BOArD");
    Gameplay gameplay;
    BOOST_CHECK(gameplay.MakeLowercase(input) == "draw board");
}

//////////////////////////////
// Castling tests for Gameplay
//////////////////////////////
BOOST_FIXTURE_TEST_CASE(testCastlingWhenNoCastling, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenOneCastling, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w', "b1"));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w', "c1"));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenTwoCastlingsWhenChoiceIsA, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("g1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->Castling('w', "a");

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w', "b1"));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w', "c1"));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenTwoCastlingsWhenChoiceIsH, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("g1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->Castling('w', "h");

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("g1"));
    ChessMan expectedKing(ChessMan(ChessManType::King, 'w', "g1"));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("f1"));
    ChessMan expectedRook(ChessMan(ChessManType::Rook, 'w', "f1"));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}

BOOST_FIXTURE_TEST_CASE(testCastlingWhenKingWasMoved, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("e1").ChangeFirstMove();

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenRookWasMoved, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("f1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("g1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("h1").ChangeFirstMove();

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("f1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("g1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenKingIsChecked, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("e2") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("e5") = ChessMan(ChessManType::Rook, 'b', "e5");

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}
BOOST_FIXTURE_TEST_CASE(testCastlingWhenCastlingFieldsIsChecked, FakeBoardFixture)
{
    fakeGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::None, 0);

    fakeGameplay->board.boardAttributes.boardState.at("d2") = ChessMan(ChessManType::None, 0);
    fakeGameplay->board.boardAttributes.boardState.at("d5") = ChessMan(ChessManType::Rook, 'b', "d5");

    fakeGameplay->Castling('w');

    ChessMan insertedKing(fakeGameplay->board.boardAttributes.boardState.at("b1"));
    ChessMan expectedKing(ChessMan(ChessManType::None, 0));
    ChessMan insertedRook(fakeGameplay->board.boardAttributes.boardState.at("c1"));
    ChessMan expectedRook(ChessMan(ChessManType::None, 0));

    BOOST_CHECK(insertedKing == expectedKing);
    BOOST_CHECK(insertedRook == expectedRook);
}

///////////////////////////////
// CheckMate tests for Gameplay
///////////////////////////////
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant1, EmptyBoardFixture)
{
    char playerColor = 'w';

    emptyGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::King, 'b', "d1");
    emptyGameplay->board.boardAttributes.kingsPositions.at('b') = "d1";
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "a8";

    emptyGameplay->board.boardAttributes.boardState.at("e1") = ChessMan(ChessManType::Queen, 'w', "e1");
    emptyGameplay->board.boardAttributes.boardState.at("a5") = ChessMan(ChessManType::Bishop, 'w', "a5");
    emptyGameplay->board.boardAttributes.boardState.at("g6") = ChessMan(ChessManType::Bishop, 'w', "g6");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant2, EmptyBoardFixture)
{
    char playerColor = 'b';

    emptyGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::Rook, 'w', "c1");
    emptyGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::King, 'w', "b1");
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "b1";

    emptyGameplay->board.boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Queen, 'b', "b2");
    emptyGameplay->board.boardAttributes.boardState.at("a3") = ChessMan(ChessManType::Bishop, 'b', "a3");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant3, EmptyBoardFixture)
{
    char playerColor = 'b';

    emptyGameplay->board.boardAttributes.boardState.at("e4") = ChessMan(ChessManType::King, 'w', "e4");
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "e4";

    emptyGameplay->board.boardAttributes.boardState.at("b4") = ChessMan(ChessManType::Rook, 'b', "b4");
    emptyGameplay->board.boardAttributes.boardState.at("d5") = ChessMan(ChessManType::Rook, 'b', "d5");
    emptyGameplay->board.boardAttributes.boardState.at("d3") = ChessMan(ChessManType::Queen, 'b', "d3");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant4, EmptyBoardFixture)
{
    char playerColor = 'w';

    emptyGameplay->board.boardAttributes.boardState.at("c4") = ChessMan(ChessManType::King, 'b', "c4");
    emptyGameplay->board.boardAttributes.kingsPositions.at('b') = "c4";

    emptyGameplay->board.boardAttributes.boardState.at("d4") = ChessMan(ChessManType::Rook, 'w', "d4");
    emptyGameplay->board.boardAttributes.boardState.at("d5") = ChessMan(ChessManType::Queen, 'w', "d5");
    emptyGameplay->board.boardAttributes.boardState.at("d3") = ChessMan(ChessManType::Rook, 'w', "d3");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenTrueVariant5, EmptyBoardFixture)
{
    char playerColor = 'w';

    emptyGameplay->board.boardAttributes.boardState.at("e6") = ChessMan(ChessManType::Rook, 'b', "e6");
    emptyGameplay->board.boardAttributes.boardState.at("d1") = ChessMan(ChessManType::King, 'b', "d1");
    emptyGameplay->board.boardAttributes.kingsPositions.at('b') = "d1";
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "a8";

    emptyGameplay->board.boardAttributes.boardState.at("e1") = ChessMan(ChessManType::Queen, 'w', "e1");
    emptyGameplay->board.boardAttributes.boardState.at("a5") = ChessMan(ChessManType::Bishop, 'w', "a5");
    emptyGameplay->board.boardAttributes.boardState.at("g6") = ChessMan(ChessManType::Bishop, 'w', "g6");
    emptyGameplay->board.boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Knight, 'w', "b2");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == true);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant6, EmptyBoardFixture)
{
    char playerColor = 'b';

    emptyGameplay->board.boardAttributes.boardState.at("h2") = ChessMan(ChessManType::Pawn, 'w', "h2");
    emptyGameplay->board.boardAttributes.boardState.at("f3") = ChessMan(ChessManType::Knight, 'w', "f3");
    emptyGameplay->board.boardAttributes.boardState.at("h1") = ChessMan(ChessManType::King, 'w', "h1");
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "h1";
    emptyGameplay->board.boardAttributes.kingsPositions.at('b') = "a8";

    emptyGameplay->board.boardAttributes.boardState.at("g6") = ChessMan(ChessManType::Rook, 'b', "g6");
    emptyGameplay->board.boardAttributes.boardState.at("g1") = ChessMan(ChessManType::Queen, 'b', "g1");
    emptyGameplay->board.boardAttributes.boardState.at("d5") = ChessMan(ChessManType::Bishop, 'b', "d5");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == true);
}

BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant2, EmptyBoardFixture)
{
    char playerColor = 'b';

    emptyGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::Queen, 'w', "c1");
    emptyGameplay->board.boardAttributes.boardState.at("b1") = ChessMan(ChessManType::King, 'w', "b1");
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "b1";

    emptyGameplay->board.boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Queen, 'b', "b2");
    emptyGameplay->board.boardAttributes.boardState.at("a3") = ChessMan(ChessManType::Bishop, 'b', "a3");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant3, EmptyBoardFixture)
{
    char playerColor = 'b';

    emptyGameplay->board.boardAttributes.boardState.at("e4") = ChessMan(ChessManType::King, 'w', "e4");
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "e4";

    emptyGameplay->board.boardAttributes.boardState.at("d5") = ChessMan(ChessManType::Rook, 'b', "d5");
    emptyGameplay->board.boardAttributes.boardState.at("d3") = ChessMan(ChessManType::Queen, 'b', "d3");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == false);
}
BOOST_FIXTURE_TEST_CASE(testCheckMateWhenFalseVariant5, EmptyBoardFixture)
{
    char playerColor = 'w';

    emptyGameplay->board.boardAttributes.boardState.at("e6") = ChessMan(ChessManType::Rook, 'b', "e6");
    emptyGameplay->board.boardAttributes.boardState.at("c1") = ChessMan(ChessManType::King, 'b', "c1");
    emptyGameplay->board.boardAttributes.kingsPositions.at('b') = "c1";
    emptyGameplay->board.boardAttributes.kingsPositions.at('w') = "a8";

    emptyGameplay->board.boardAttributes.boardState.at("e1") = ChessMan(ChessManType::Queen, 'w', "e1");
    emptyGameplay->board.boardAttributes.boardState.at("a5") = ChessMan(ChessManType::Bishop, 'w', "a5");
    emptyGameplay->board.boardAttributes.boardState.at("g6") = ChessMan(ChessManType::Bishop, 'w', "g6");
    emptyGameplay->board.boardAttributes.boardState.at("b2") = ChessMan(ChessManType::Knight, 'w', "b2");

    emptyGameplay->board.CalculateMovesBoardAndReactionBoardWithNeutralKings();
    bool checkMate(emptyGameplay->SwitchPlayerAndLookForCheckMateOrCheck(playerColor));

    BOOST_CHECK(checkMate == false);
}

BOOST_AUTO_TEST_SUITE_END()
