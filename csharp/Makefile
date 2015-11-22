all: MainClass.exe

MainClass.exe: MainClass.cs Function.cs MainSolver.cs MyThread.cs Options.cs Scanner.cs SolverThread.cs
	mcs MainClass.cs Function.cs MainSolver.cs MyThread.cs Options.cs Scanner.cs SolverThread.cs
run: MainClass.exe
	mono MainClass.exe
clean:
	rm -rf *.exe


