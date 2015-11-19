#include <Options.h>
#include <Utils.h>

#include <iostream>

Options::Options() :
    m_isNumPartitionsSet(false),
    m_isASet(false),
    m_isBSet(false),
    m_isFxSet(false)
{
}

bool Options::parse(int argc, char **argv) {
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    for (size_t i = 1; i < args.size(); i += 2) {
        std::string command = args[i];
        if (i+1 >= args.size()) {
            continue;
        }
        std::string arg = args[i+1];

        bool ok = false;
        int intArg;
        double doubleArg;

        if (command == "--num_partitions") {
            intArg = Utils::string2int(arg, &ok);
            if (!ok) {
                std::cout << "Can't parse the argument for the --num_partitions command line option: " << arg << std::endl;
                return false;
            }
            m_numPartitions = intArg;
            m_isNumPartitionsSet = true;
        } else if (command == "--a") {
            doubleArg = Utils::string2double(arg);
            m_a = doubleArg;
            m_isASet = true;
        } else if (command == "--b") {
            doubleArg = Utils::string2double(arg);
            m_b = doubleArg;
            m_isBSet = true;
        } else if (command == "--function") {
            intArg = Utils::string2int(arg);
            if (intArg < 0 || intArg > 9) {
                std::cout << "The argument for the --function command line option is out of range [0,9]: " << arg << std::endl;
                return false;
            }
            m_fx = intArg;
            m_isFxSet = true;
        } else {
            printf("Command unknown!: %s\n", command.c_str());
            fflush(stdout);
            return false;
        }
    }
    if (!m_isNumPartitionsSet) {
        printf("Make sure to add the --num_partitions option! Error\n");
        fflush(stdout);
        return false;
    }

    if (!m_isASet) {
        printf("Make sure to add the --a option! Error\n");
        fflush(stdout);
        return false;
    }

    if (!m_isBSet) {
        printf("Make sure to add the --b option! Error\n");
        fflush(stdout);
        return false;
    }

    if (!m_isFxSet) {
        printf("Make sure to add the --function option ([0-9])! Error\n");
        fflush(stdout);
        return false;
    }

    return true;
}
