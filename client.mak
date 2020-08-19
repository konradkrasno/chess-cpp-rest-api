CFLAGS=-Wall
LD_FLAGS=-L/chess-client/restc-cpp/lib -lrestc-cpp -lz -lssl -lcrypto -lpthread -lboost_system \
	-lboost_program_options -lboost_filesystem -lboost_date_time -lboost_context \
	-lboost_coroutine -lboost_chrono -lboost_log -lboost_thread -lboost_log_setup \
	-lboost_regex -lboost_atomic -lpthread

objects=client.o Gameplay.o subsidiary.o ChessMan.o Move.o \
 BoardAttributes.o PawnMoves.o UpdateAttributes.o KnightMoves.o \
 QueenMoves.o RookMoves.o BishopMoves.o KingMoves.o Board.o Provider.o

client: $(objects)
		g++ $(CFLAGS) $^ -o $@ $(LD_FLAGS)

BasicController.o: BasicController.cpp BasicController.h
BishopMoves.o: BishopMoves.cpp BishopMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h
Board.o: Board.cpp Board.h subsidiary.h Move.h BoardAttributes.h \
 ChessMan.h PawnMoves.h UpdateAttributes.h KnightMoves.h QueenMoves.h \
 RookMoves.h BishopMoves.h KingMoves.h Provider.h
BoardAttributes.o: BoardAttributes.cpp BoardAttributes.h subsidiary.h \
 ChessMan.h
ChessMan.o: ChessMan.cpp subsidiary.h ChessMan.h
Gameplay.o: Gameplay.cpp Gameplay.h subsidiary.h ChessMan.h Move.h \
 BoardAttributes.h PawnMoves.h UpdateAttributes.h KnightMoves.h \
 QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h Provider.h
KingMoves.o: KingMoves.cpp KingMoves.h subsidiary.h UpdateAttributes.h \
 ChessMan.h
KnightMoves.o: KnightMoves.cpp KnightMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h
Move.o: Move.cpp Move.h BoardAttributes.h subsidiary.h ChessMan.h \
 PawnMoves.h UpdateAttributes.h KnightMoves.h QueenMoves.h RookMoves.h \
 BishopMoves.h KingMoves.h
PawnMoves.o: PawnMoves.cpp PawnMoves.h subsidiary.h UpdateAttributes.h \
 ChessMan.h
Provider.o: Provider.cpp Provider.h
QueenMoves.o: QueenMoves.cpp QueenMoves.h RookMoves.h subsidiary.h \
 UpdateAttributes.h ChessMan.h BishopMoves.h
RookMoves.o: RookMoves.cpp RookMoves.h subsidiary.h UpdateAttributes.h \
 ChessMan.h
UpdateAttributes.o: UpdateAttributes.cpp UpdateAttributes.h subsidiary.h \
 ChessMan.h
client.o: client.cpp Gameplay.h subsidiary.h ChessMan.h Move.h \
 BoardAttributes.h PawnMoves.h UpdateAttributes.h KnightMoves.h \
 QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h Provider.h
subsidiary.o: subsidiary.cpp subsidiary.h

.PHONY: clean
 
clean:
		rm -f $(objects)
