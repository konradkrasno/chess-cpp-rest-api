CC=g++
CFLAGS=-Wall
sources=BishopMoves.cpp BoardAttributes.cpp Board.cpp chess.cpp \
 ChessMan.cpp Gameplay.cpp KingMoves.cpp KnightMoves.cpp \
 Move.cpp PawnMoves.cpp QueenMoves.cpp RookMoves.cpp subsidiary.cpp \
 UpdateAttributes.cpp
objects=$(sources:.cpp=.o)

chess_game: $(objects)
		g++ -lm $^ -o $@

BishopMoves.o: BishopMoves.cpp BishopMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h
BoardAttributes.o: BoardAttributes.cpp BoardAttributes.h subsidiary.h \
 ChessMan.h
Board.o: Board.cpp Board.h subsidiary.h Move.h BoardAttributes.h \
 ChessMan.h PawnMoves.h UpdateAttributes.h KnightMoves.h QueenMoves.h \
 RookMoves.h BishopMoves.h KingMoves.h
chess.o: chess.cpp Gameplay.h subsidiary.h ChessMan.h Move.h \
 BoardAttributes.h PawnMoves.h UpdateAttributes.h KnightMoves.h \
 QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h
ChessMan.o: ChessMan.cpp subsidiary.h ChessMan.h
Gameplay.o: Gameplay.cpp Gameplay.h subsidiary.h ChessMan.h Move.h \
 BoardAttributes.h PawnMoves.h UpdateAttributes.h KnightMoves.h \
 QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h
KingMoves.o: KingMoves.cpp KingMoves.h subsidiary.h UpdateAttributes.h \
 ChessMan.h
KnightMoves.o: KnightMoves.cpp KnightMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h
Move.o: Move.cpp Move.h BoardAttributes.h subsidiary.h ChessMan.h \
 PawnMoves.h UpdateAttributes.h KnightMoves.h QueenMoves.h RookMoves.h \
 BishopMoves.h KingMoves.h
PawnMoves.o: PawnMoves.cpp PawnMoves.h subsidiary.h UpdateAttributes.h \
 ChessMan.h
QueenMoves.o: QueenMoves.cpp QueenMoves.h RookMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h BishopMoves.h
RookMoves.o: RookMoves.cpp RookMoves.h subsidiary.h UpdateAttributes.h \
 ChessMan.h
subsidiary.o: subsidiary.cpp subsidiary.h
Tests.o: Tests.cpp Move.h BoardAttributes.h subsidiary.h ChessMan.h \
 PawnMoves.h UpdateAttributes.h KnightMoves.h QueenMoves.h RookMoves.h \
 BishopMoves.h KingMoves.h Gameplay.h Board.h
UpdateAttributes.o: UpdateAttributes.cpp UpdateAttributes.h subsidiary.h \
 ChessMan.h

.PHONY: clean
 
clean:
		rm -f chess_game $(objects)
