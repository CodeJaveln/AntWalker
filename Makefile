build:
	gcc -Iinclude -Wall -Werror -std=c99 ./src/*.c -lSDL2 -o ./bin/game

win:
	i686-w64-mingw32-gcc -o bin/game.exe src/*.c -I./include -I./cross_include -L./cross_lib -lmingw32 -lSDL2 -lSDL2main
	cp ./cross_lib/SDL2.dll ./bin

run:
	./bin/game

clear:
	rm -rf ./bin/*