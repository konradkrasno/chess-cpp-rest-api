CFLAGS=-Wall
objects=chess.o Gameplay.o subsidiary.o ChessMan.o Move.o \
 BoardAttributes.o PawnMoves.o UpdateAttributes.o KnightMoves.o \
 QueenMoves.o RookMoves.o BishopMoves.o KingMoves.o Board.o

chess: $(objects)
		g++ $(CFLAGS) $^ -o $@

BasicController.o: BasicController.cpp BasicController.h
BishopMoves.o: BishopMoves.cpp BishopMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h
Board.o: Board.cpp Board.h subsidiary.h Move.h BoardAttributes.h \
 ChessMan.h PawnMoves.h UpdateAttributes.h KnightMoves.h QueenMoves.h \
 RookMoves.h BishopMoves.h KingMoves.h
BoardAttributes.o: BoardAttributes.cpp BoardAttributes.h subsidiary.h \
 ChessMan.h
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
Service.o: Service.cpp Service.h BasicController.h Gameplay.h \
 subsidiary.h ChessMan.h Move.h BoardAttributes.h PawnMoves.h \
 UpdateAttributes.h KnightMoves.h QueenMoves.h RookMoves.h BishopMoves.h \
 KingMoves.h Board.h
UpdateAttributes.o: UpdateAttributes.cpp UpdateAttributes.h subsidiary.h \
 ChessMan.h
chess.o: chess.cpp Gameplay.h subsidiary.h ChessMan.h Move.h \
 BoardAttributes.h PawnMoves.h UpdateAttributes.h KnightMoves.h \
 QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h
client.o: client.cpp Gameplay.h subsidiary.h ChessMan.h Move.h \
 BoardAttributes.h PawnMoves.h UpdateAttributes.h KnightMoves.h \
 QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h
server.o: server.cpp Service.h BasicController.h Gameplay.h subsidiary.h \
 ChessMan.h Move.h BoardAttributes.h PawnMoves.h UpdateAttributes.h \
 KnightMoves.h QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h
subsidiary.o: subsidiary.cpp subsidiary.h

.PHONY: clean
 
clean:
		rm -f $(objects)
