#include <Options.h>
#include <Utils.h>

#include <cstdio>

Options::Options() :
    m_isNumPartitionsSet(false),
    m_isASet(false),
    m_isBSet(false),
    m_isFxSet(false)
{
}

bool Options::parse(int argc, char **argv) {
    // convert every argument to std::string for easy of equality testing
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    bool valueToReturn = true;

    for (size_t i = 1; i < args.size(); i += 2) {
        // take an argument and the next and asume is the command and it
        // respective argument
        std::string command = args[i];
        if (i+1 >= args.size()) {
            continue;
        }
        std::string arg = args[i+1];

        bool ok = false;

        if (command == "--num_partitions") {
            m_numPartitions = Utils::string2int(arg, &ok);
            if (ok) {
                m_isNumPartitionsSet = true;
            } else {
                std::cout << "Can't parse the argument for the "
                          << "--num_partitions command line option: "
                          << arg << std::endl;
                valueToReturn = false;
            }
        } else if (command == "--a") {
            m_a = Utils::string2double(arg);
            m_isASet = true;
        } else if (command == "--b") {
            m_b = Utils::string2double(arg);
            m_isBSet = true;
        } else if (command == "--function") {
            m_fx = Utils::string2int(arg);
            if (m_fx < 0 || m_fx > 9) {
                std::cout << "The argument for the --function command line "
                          << "option is out of range [0,9]: " << arg
                          << std::endl;
                valueToReturn = false;
            } else {
                m_isFxSet = true;
            }
        } else {
            printf("Command unknown!: %s\n", command.c_str());
            fflush(stdout);
            valueToReturn = false;
        }
    }

    if (!m_isNumPartitionsSet) {
        printf("Make sure to add the --num_partitions option! Error\n");
        fflush(stdout);
        valueToReturn = false;
    }

    if (!m_isASet) {
        printf("Make sure to add the --a option! Error\n");
        fflush(stdout);
        valueToReturn = false;
    }

    if (!m_isBSet) {
        printf("Make sure to add the --b option! Error\n");
        fflush(stdout);
        valueToReturn = false;
    }

    if (!m_isFxSet) {
        printf("Make sure to add the --function option ([0-9])! Error\n");
        fflush(stdout);
        valueToReturn = false;
    }

    return valueToReturn;
}
