package cl.usach.so;

/**
 * Created by rene on 22-11-15.
 */
public class Options {

    public boolean isNumPartitionsSet;
    public boolean isASet;
    public boolean isBSet;
    public boolean isFxSet;

    public int numPartitions;
    public double a;
    public double b;
    public int fx;

    public boolean parse(String []argv) {
        boolean valueToReturn = true;

        for (int i = 0; i < argv.length; i++) {
            String command = argv[i];
            if (i+1 >= argv.length) {
                continue;
            }
            String arg = argv[i+1];

            if ("--num_partitions".equals(command)) {
                try {
                    numPartitions = Integer.parseInt(arg);
                    isNumPartitionsSet = true;
                } catch (NumberFormatException nfe) {
                    System.out.println("Can't parse the argument for --num_partitions");
                    System.out.println(nfe.getMessage());
                    valueToReturn = false;
                }
            } else if ("--a".equals(command)) {
                try {
                    a = Double.parseDouble(arg);
                    isASet = true;
                } catch (NumberFormatException nfe) {
                    System.out.println("Can't parse the argument for --a");
                    System.out.println(nfe.getMessage());
                    valueToReturn = false;
                }
            } else if ("--b".equals(command)) {
                try {
                    b = Double.parseDouble(arg);
                    isBSet = true;
                } catch (NumberFormatException nfe) {
                    System.out.println("Can't parse the argument for --b");
                    System.out.println(nfe.getMessage());
                    valueToReturn = false;
                }
            } else if ("--function".equals(command)) {
                try {
                    fx = Integer.parseInt(arg);
                    isFxSet = true;
                } catch (NumberFormatException nfe) {
                    System.out.println("Can't parse the argument for --function");
                    System.out.println(nfe.getMessage());
                    valueToReturn = false;
                }
            }
        }

        if (!isNumPartitionsSet) {
            System.out.println("Make sure to add the --num_partitions option! Error");
            valueToReturn = false;
        }

        if (!isASet) {
            System.out.println("Make sure to add the --a option! Error");
            valueToReturn = false;
        }

        if (!isBSet) {
            System.out.println("Make sure to add the --b option! Error");
            valueToReturn = false;
        }

        if (!isFxSet) {
            System.out.println("Make sure to add the --function option ([0-9])! Error");
            valueToReturn = false;
        }

        return valueToReturn;
    }

}
