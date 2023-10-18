# Compiler to use
CC = g++

# Flags to pass to the compiler, including C++11 support
CFLAGS = -Wall -std=c++11

spell.exe: spellcheck.o hash.o
	$(CC) -o spell.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	$(CC) $(CFLAGS) -c spellcheck.cpp

hash.o: hash.cpp hash.h
	$(CC) $(CFLAGS) -c hash.cpp

debug:
	$(CC) -g -o spellDebug.exe spellcheck.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
