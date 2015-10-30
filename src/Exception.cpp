#include <Exception.h>

Exception::Exception(const std::string &message) :
   std::runtime_error(message)
{
}

Exception Exception::build(const std::string &message, int code) {
   return Exception(message + " (" + Utils::int2string(code) + ").");
}
