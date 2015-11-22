using System;
/**
 * @brief The Function class represents a formula which will be used along with the integration threads.
 */
public abstract class Function {
	private String name;
	
	public Function(String name) {
		this.name = name;
	}
	
	/**
     * @brief Evaluate Definition of the formula.
     * @param x X coordinate to evalue for this function formlua.
     * @return Double, with the Y coordinate for this formula evaluated at x.
     */
	public abstract double Evaluate(double x);
	
	/**
     * @brief GetName Gets the name of the formula.
     */
	public String GetName() {
		return name;
	}
}