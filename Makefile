.PHONY: clean

main: main.c sqlite3.o
	gcc main.c sqlite3.o -o main

sqlite3.o: deps/sqlite/sqlite3.c
	gcc -c deps/sqlite/sqlite3.c
