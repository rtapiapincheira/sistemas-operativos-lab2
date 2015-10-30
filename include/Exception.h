#ifndef __EXCEPTION_H_
#define __EXCEPTION_H_

#include <string>
#include <stdexcept>

#include <Utils.h>

class Exception : public std::runtime_error {
public:
   Exception(const std::string &message);

   static Exception build(const std::string &message, int code = 0);
};

#endif // __EXCEPTION_H_
