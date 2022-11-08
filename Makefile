CFLAGS = -g -Wall
INC = -I include -I /usr/local/cuda/include
SFML = -lsfml-graphics -lsfml-window -lsfml-system
CUDA = -lcuda -lcudart

run_game: main.o game_manager.o cpu_board.o renderer.o gpu_board.o Makefile
	g++ ${CFLAGS} -L /usr/local/cuda/lib64/ -o run_game main.o game_manager.o cpu_board.o gpu_board.o renderer.o ${SFML} ${CUDA}

main.o: src/main.cpp include/game_manager.h include/renderer.h include/board.h Makefile
	g++ ${CFLAGS} ${INC} -c src/main.cpp

speed_test: speed_test.o game_manager.o cpu_board.o renderer.o gpu_board.o Makefile
	g++ ${CFLAGS} -L /usr/local/cuda/lib64/ -o speed_test speed_test.o game_manager.o cpu_board.o gpu_board.o renderer.o ${SFML} ${CUDA}
 
speed_test.o: src/speed_test.cpp include/game_manager.h include/renderer.h include/board.h Makefile 
	g++ ${CFLAGS} ${INC} -c src/speed_test.cpp

cpu_board.o: src/cpu_board.cpp include/board.h Makefile
	g++ ${CFLAGS} ${INC} -c src/cpu_board.cpp

gpu_board.o: src/gpu_board.cu include/board.h Makefile
	nvcc -g -G -I include -c src/gpu_board.cu

renderer.o: src/renderer.cpp include/renderer.h include/exceptions.h Makefile
	g++ ${CFLAGS} ${INC} -c src/renderer.cpp

game_manager.o: src/game_manager.cpp include/game_manager.h include/exceptions.h include/renderer.h include/board.h Makefile
	g++ ${CFLAGS} ${INC} -c src/game_manager.cpp

clean:
	rm -f $(wildcard *.o) run_game