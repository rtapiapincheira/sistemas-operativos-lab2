all: MainClass.exe

MainClass.exe: MainClass.cs Function.cs MainSolver.cs MyThread.cs Options.cs Scanner.cs SolverThread.cs
	mcs MainClass.cs Function.cs MainSolver.cs MyThread.cs Options.cs Scanner.cs SolverThread.cs
run: MainClass.exe
	mono MainClass.exe --num_partitions 100000 --a 0 --b 2 --function 0
clean:
	rm -rf *.exe


