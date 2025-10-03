.PHONY: build clean
build:
	gcc -std=c99 -g main.c functii.c functii.h -o ./tema2
run:
	./tema2
clean:
	rm -rf ./tema2