using System;

public class Options {
	public bool isNumPartitionsSet;
    public bool isASet;
    public bool isBSet;
    public bool isFxSet;

    public int numPartitions;
    public double a;
    public double b;
    public int fx;

    public bool parse(String []argv) {
        bool valueToReturn = true;

        for (int i = 0; i < argv.Length; i++) {
            String command = argv[i];
            if (i+1 >= argv.Length) {
                continue;
            }
            String arg = argv[i+1];

            if ("--num_partitions".Equals(command)) {
                try {
                    numPartitions = Convert.ToInt32(arg);
                    isNumPartitionsSet = true;
                } catch (FormatException e) {
                    Console.WriteLine("Can't parse the argument for --num_partitions");
                    Console.WriteLine(e.Message);
                    valueToReturn = false;
                }
            } else if ("--a".Equals(command)) {
                try {
                    a = Convert.ToDouble(arg);
                    isASet = true;
                } catch (FormatException e) {
                    Console.WriteLine("Can't parse the argument for --a");
                    Console.WriteLine(e.Message);
                    valueToReturn = false;
                }
            } else if ("--b".Equals(command)) {
                try {
                    b = Convert.ToDouble(arg);
                    isBSet = true;
                } catch (FormatException e) {
                    Console.WriteLine("Can't parse the argument for --b");
                    Console.WriteLine(e.Message);
                    valueToReturn = false;
                }
            } else if ("--function".Equals(command)) {
                try {
                    fx = Convert.ToInt32(arg);
                    isFxSet = true;
                } catch (FormatException e) {
                    Console.WriteLine("Can't parse the argument for --function");
                    Console.WriteLine(e.Message);
                    valueToReturn = false;
                }
            }
        }

        if (!isNumPartitionsSet) {
            Console.WriteLine("Make sure to add the --num_partitions option! Error");
            valueToReturn = false;
        }

        if (!isASet) {
            Console.WriteLine("Make sure to add the --a option! Error");
            valueToReturn = false;
        }

        if (!isBSet) {
            Console.WriteLine("Make sure to add the --b option! Error");
            valueToReturn = false;
        }

        if (!isFxSet) {
 	        Console.WriteLine("Make sure to add the --function option ([0-9])! Error");
            valueToReturn = false;
        }

        return valueToReturn;
    }
}