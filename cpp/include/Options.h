#ifndef __OPTIONS_H_
#define __OPTIONS_H_

#include <string>
#include <vector>

/**
 * @brief The Options class handles the processing logic for the command line
 * arguments for the application. If a parameter is set through the command line
 * options, the corresponding m_isVARIABLESet will be set to true, and its value
 * will be able to be taken from the m_VARIABLE instance variable.
 */
class Options {
public: // for ease of accessing only!
    int m_numPartitions; bool m_isNumPartitionsSet;
    double m_a;          bool m_isASet;
    double m_b;          bool m_isBSet;
    int m_fx;            bool m_isFxSet;

public:
    /**
     * @brief Options Sets false for everything (no value is parsed yet!).
     */
    Options();

    /**
     * @param argc Number of arguments (as supplied to the main arguments).
     * @param argv Actual string arguments passed to the application.
     * @return true if all the parameters were recognized ok, otherwise false.
     */
    bool parse(int argc, char **argv);
};

#endif // __OPTIONS_H_
