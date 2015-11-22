using System;
using System.Collections;

public class F0 : Function {
	public F0() : base("cos(x)") {}
	public override double Evaluate(double x) {return Math.Cos(x);}
}

public class F1 : Function {
	public F1() : base("sin(x)") {}
	public override double Evaluate(double x) {return Math.Sin(x);}
}

public class F2 : Function {
	public F2() : base("x2") {}
	public override double Evaluate(double x) {return Math.Pow(x, 2);}
}

public class F3 : Function {
	public F3() : base("exp(x)") {}
	public override double Evaluate(double x) {return Math.Exp(x);}
}

public class F4 : Function {
	public F4() : base("x2 exp(x)") {}
	public override double Evaluate(double x) {return Math.Pow(x,2) * Math.Exp(x);}
}

public class F5 : Function {
	public F5() : base("7/4 x3 exp(x2) + 2x") {}
	public override double Evaluate(double x) {return 7.0/4.0 * Math.Pow(x,3) * Math.Exp(Math.Pow(x, 2)) + 2 * x;}
}

public class F6 : Function {
	public F6() : base("3x cos(4x) + 2") {}
	public override double Evaluate(double x) {return 3 * x + Math.Cos(4 * x) + 2;}
}

public class F7 : Function {
	public F7() : base("2x") {}
	public override double Evaluate(double x) {return 2 * x;}
}

public class F8 : Function {
	public F8() : base("4 + x") {}
	public override double Evaluate(double x) {return 4.0 + x;}
}

public class F9 : Function {
	public F9() : base("2x2 + x + 6") {}
	public override double Evaluate(double x) {return 2 * Math.Pow(x, 2) + x + 6;}
}

public class MainClass
{
	private static Function[] functions = new Function[] {
		new F0(),
	    new F1(),
	    new F2(),
	    new F3(),
	    new F4(),
	    new F5(),
	    new F6(),
	    new F7(),
	    new F8(),
	    new F9()
	};

    static void Main(String[] args) {

    	Options options = new Options();
    	if (!options.parse(args)) {
    		//return;
    	}

	    Scanner scanner = new Scanner();

    	// Take all the parameters from the input
	    double a, b;
	    int N;
	    int fx;
	    int _realN;

        // ------ lower limit input -----
        Console.Write("Ingrese a: ");
        if (options.isASet) {
            a = options.a;
            Console.WriteLine(a);
        } else {
            a = scanner.nextDouble();
        }

        // ------ upper limit input -----
        Console.Write("Ingrese b: ");
        if (options.isBSet) {
            b = options.b;
            Console.WriteLine(b);
        } else {
            b = scanner.nextDouble();
        }

        // ------ number of partitions input -----
        Console.Write("Ingrese N: ");
        if (options.isNumPartitionsSet) {
            N = options.numPartitions;
            Console.WriteLine(N);
        } else {
            N = scanner.nextInt();
        }
        _realN = 3 * N;

        Console.WriteLine("Seleccione la funcion a integrar (1 - {0}):", functions.Length);
        for (int i = 0; i < functions.Length; i++) {
            Console.WriteLine("   opcion #{0}: {1}", i, functions[i].GetName());
        }

        // ------ function index input ------
        if (options.isFxSet) {
            Console.Write(" ingrese la opcion: ");
            fx = options.fx;
            Console.WriteLine(fx);
        } else {
            do {
                Console.Write(" ingrese la opcion: ");
                fx = scanner.nextInt();
            } while (fx < 0 || fx >= functions.Length);
        }

        Console.WriteLine();

        // ----- begin to calculate the final results -----

        double h = (b - a) / _realN;

        Console.WriteLine("Resultado Integracion:");
        Console.WriteLine("==========================");
        Console.WriteLine();

        Console.WriteLine("Funcion a integrar      : {0}", functions[fx].GetName());
        Console.WriteLine("Numero de particiones   : 3 * (N={0}) = {1}", N, _realN);
        Console.WriteLine("Limite inferior         : {0}", a);
        Console.WriteLine("Limite superior         : {0}", b);
        Console.WriteLine("Paso (h = (b-a)/N)      : {0}", h);

        // ----- solve and print the final result -----------

        MainSolver solver = new MainSolver(a, b, h, _realN, functions[fx]);
        double result = solver.ExecuteThreads();
        Console.WriteLine("Resultado de integracion: {0}", result);
    }
}