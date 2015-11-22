SRC_PATH=cl/usach/so

all: bin/cl/usach/so/Main.class

bin/cl/usach/so/Main.class: src/$(SRC_PATH)/Function.java src/$(SRC_PATH)/Main.java src/$(SRC_PATH)/MainSolver.java src/$(SRC_PATH)/Options.java src/$(SRC_PATH)/SolverThread.java
	mkdir -p bin && javac -d bin -sourcepath src src/$(SRC_PATH)/*.java

run: bin/cl/usach/so/Main.class
	java -cp bin cl/usach/so/Main

clean:
	rm -rf bin


