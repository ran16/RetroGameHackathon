compiler = clang++ -Wall

all: bin/main.out

bin/main.out: bin/main.o
	${compiler} $^  -lsfml-graphics -lsfml-window -lsfml-system -o bin/main.out

bin/main.o: src/main.cpp
	${compiler} src/main.cpp -c -o bin/main.o
