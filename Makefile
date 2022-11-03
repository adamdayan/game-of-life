CFLAGS = -g -Wall -MMD
INC = -I include
SFML = -lsfml-graphics -lsfml-window -lsfml-system

run_game: main.o game_manager.o board.o renderer.o Makefile
	g++ ${CFLAGS} -o run_game main.o game_manager.o board.o renderer.o ${SFML}

main.o: src/main.cpp include/game_manager.h include/renderer.h include/board.h Makefile
	g++ ${CFLAGS} ${INC} -c src/main.cpp

board.o: src/board.cpp include/board.h Makefile
	g++ ${CFLAGS} ${INC} -c src/board.cpp

renderer.o: src/renderer.cpp include/renderer.h include/exceptions.h Makefile
	g++ ${CFLAGS} ${INC} -c src/renderer.cpp

game_manager.o: src/game_manager.cpp include/game_manager.h include/exceptions.h include/renderer.h include/board.h Makefile
	g++ ${CFLAGS} ${INC} -c src/game_manager.cpp

clean:
	rm -f $(wildcard *.o)
	rm -f run_game 