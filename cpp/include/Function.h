#ifndef __FUNCTION_H_
#define __FUNCTION_H_

#include <string>
#include <cmath>

/**
 * @brief The Function class represents a formula which will be used along with
 * the integration threads.
 */
class Function {
private:
    std::string m_name;
public:
    Function(const std::string &name) : m_name(name) {}
    /**
     * @brief evaluate Definition of the formula.
     * @param x X coordinate to evalue for this function formlua.
     * @return Double, whth the Y coordinate for this formula evaluated at x.
     */
    virtual double evaluate(double x) = 0;

    /**
     * @brief getName Gets the name of the formula.
     */
    virtual std::string getName() { return m_name; }
};

/** Creates a Function subclass with the given class name, argument name and
 * formula. */
#define DEFINE_FORMULA(CLS_NAME, STR, X, FORMULA) \
class CLS_NAME : public Function {\
public:\
    CLS_NAME() : Function(STR) {}\
    virtual double evaluate(double X) {return FORMULA;}\
}

/*
// Example to define a class pepito that returns a dummy function.

class Pepito : public Function {
    Pepito() : Function("pepito") {

    }
    ~Pepito() {
    }
    virtual double evaluate(double x) {
        return x*x*x + 2 + 2* ::exp(2);
    }
};

DEFINE_FORMULA(Pepito, "pepito", x, x*x*x + 2 + 2* ::exp(2));
*/

#endif // __FUNCTION_H_
