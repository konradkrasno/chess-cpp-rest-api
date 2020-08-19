CFLAGS=-Wall
LD_FLAGS=-lcpprest -lpthread -lboost_system -lssl -lcrypto

objects=BasicController.o BoardAttributes.o \
 ChessMan.o Service.o server.o subsidiary.o

server: $(objects)
		g++ $(CFLAGS) $^ -o $@ $(LD_FLAGS)

BasicController.o: BasicController.cpp BasicController.h
BoardAttributes.o: BoardAttributes.cpp BoardAttributes.h subsidiary.h \
 ChessMan.h
ChessMan.o: ChessMan.cpp subsidiary.h ChessMan.h
Service.o: Service.cpp Service.h BasicController.h Gameplay.h \
 subsidiary.h ChessMan.h Move.h BoardAttributes.h PawnMoves.h \
 UpdateAttributes.h KnightMoves.h QueenMoves.h RookMoves.h BishopMoves.h \
 KingMoves.h Board.h
server.o: server.cpp Service.h BasicController.h Gameplay.h subsidiary.h \
 ChessMan.h Move.h BoardAttributes.h PawnMoves.h UpdateAttributes.h \
 KnightMoves.h QueenMoves.h RookMoves.h BishopMoves.h KingMoves.h Board.h
subsidiary.o: subsidiary.cpp subsidiary.h

.PHONY: clean
 
clean:
		rm -f program $(objects)
