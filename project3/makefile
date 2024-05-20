CXXFLAGS = -std=c++11

useGraph.exe: useGraph.o graph.o heap.o hash.o
	g++ $(CXXFLAGS) -o useGraph.exe useGraph.o graph.o heap.o hash.o

useGraph.o: useGraph.cpp graph.h
	g++ $(CXXFLAGS) -c useGraph.cpp

graph.o: graph.cpp graph.h
	g++ $(CXXFLAGS) -c graph.cpp

heap.o: heap.cpp heap.h
	g++ $(CXXFLAGS) -c heap.cpp

hash.o: hash.cpp hash.h
	g++ $(CXXFLAGS) -c hash.cpp

debug:
	g++ $(CXXFLAGS) -g -o useGraphDebug.exe useGraph.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
