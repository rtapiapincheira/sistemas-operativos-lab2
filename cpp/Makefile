all: main
run: main
	./main --num_partitions 100000 --a 0 --b 2 --function 0

INCLUDES=include/Function.h include/MainSolver.h include/Options.h include/SolverThread.h include/Thread.h include/Utils.h
OBJS = main.o MainSolver.o Options.o SolverThread.o Thread.o Utils.o

main: $(OBJS)
	g++ -o main $(OBJS) -lpthread

main.o: src/main.cpp $(INCLUDES)
	g++ -c -o main.o -Iinclude src/main.cpp

MainSolver.o: src/MainSolver.cpp $(INCLUDES)
	g++ -c -o MainSolver.o -Iinclude src/MainSolver.cpp

Options.o: src/Options.cpp $(INCLUDES)
	g++ -c -o Options.o -Iinclude src/Options.cpp

SolverThread.o: src/SolverThread.cpp $(INCLUDES)
	g++ -c -o SolverThread.o -Iinclude src/SolverThread.cpp

Thread.o: src/Thread.cpp $(INCLUDES)
	g++ -c -o Thread.o -Iinclude src/Thread.cpp -lpthread

Utils.o: src/Utils.cpp $(INCLUDES)
	g++ -c -o Utils.o -Iinclude src/Utils.cpp

clean:
	rm -rf main *.o

