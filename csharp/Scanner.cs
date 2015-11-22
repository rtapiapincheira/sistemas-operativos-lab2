using System;

public class Scanner {
	public int nextInt() {
		String line = Console.ReadLine();
		try {
			return Convert.ToInt32(line);
		} catch(FormatException e) {
			Console.WriteLine("Error while formatting '{0}': {1}", line, e.Message);
		}
		return 0;
	}
	
	public double nextDouble() {
		String line = Console.ReadLine();
		try {
			return Convert.ToDouble(line);
		} catch(FormatException e) {
			Console.WriteLine("Error while formatting '{0}': {1}", line, e.Message);
		}
		return 0.0;
	}
}