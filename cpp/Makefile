all: main
run: main
	./main --num_partitions 100000 --a 0 --b 2 --function 0

INCLUDES=include/Function.h include/OpenmpSolver.h include/Options.h include/Solver.h include/Thread.h include/ThreadedSolver.h include/Utils.h
OBJS = main.o OpenmpSolver.o Options.o Solver.o Thread.o ThreadedSolver.o Utils.o

main: $(OBJS)
	g++ -o main $(OBJS) -lpthread -fopenmp

main.o: src/main.cpp $(INCLUDES)
	g++ -c -o main.o -Iinclude src/main.cpp

OpenmpSolver.o: src/OpenmpSolver.cpp $(INCLUDES)
	g++ -c -o OpenmpSolver.o -Iinclude src/OpenmpSolver.cpp -fopenmp

Options.o: src/Options.cpp $(INCLUDES)
	g++ -c -o Options.o -Iinclude src/Options.cpp

Solver.o: src/Solver.cpp $(INCLUDES)
	g++ -c -o Solver.o -Iinclude src/Solver.cpp

Thread.o: src/Thread.cpp $(INCLUDES)
	g++ -c -o Thread.o -Iinclude src/Thread.cpp -lpthread

ThreadedSolver.o: src/ThreadedSolver.cpp $(INCLUDES)
	g++ -c -o ThreadedSolver.o -Iinclude src/ThreadedSolver.cpp

Utils.o: src/Utils.cpp $(INCLUDES)
	g++ -c -o Utils.o -Iinclude src/Utils.cpp

clean:
	rm -rf main *.o

