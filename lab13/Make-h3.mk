CC = g++ -Wall
hello.out : hello.cpp
	$(CC) $< -o $@
