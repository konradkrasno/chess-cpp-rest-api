CFLAGS=-Wall
LD_FLAGS=-lcpprest -lpthread -lboost_system -lssl -lcrypto

objects=server.o Service.o BasicController.o BoardAttributes.o \
 subsidiary.o ChessMan.o Models.o

server: $(objects)
		g++ $(CFLAGS) $^ -o $@ $(LD_FLAGS)

BasicController.o: BasicController.cpp BasicController.h
BoardAttributes.o: BoardAttributes.cpp BoardAttributes.h subsidiary.h \
 ChessMan.h
ChessMan.o: ChessMan.cpp subsidiary.h ChessMan.h
Models.o: Models.cpp Models.h
Service.o: Service.cpp Service.h BasicController.h BoardAttributes.h \
 subsidiary.h ChessMan.h Models.h
server.o: server.cpp Service.h BasicController.h BoardAttributes.h \
 subsidiary.h ChessMan.h Models.h
subsidiary.o: subsidiary.cpp subsidiary.h

.PHONY: clean
 
clean:
		rm -f program $(objects)
