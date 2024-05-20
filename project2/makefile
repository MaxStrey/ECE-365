CXXFLAGS = -std=c++11

useHeap.exe: useHeap.o heap.o hash.o
	g++ $(CXXFLAGS) -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	g++ $(CXXFLAGS) -c useHeap.cpp

heap.o: heap.cpp heap.h
	g++ $(CXXFLAGS) -c heap.cpp

hash.o: hash.cpp hash.h
	g++ $(CXXFLAGS) -c hash.cpp

debug:
	g++ $(CXXFLAGS) -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
