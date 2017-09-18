#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>

template <class T>
std::string to_string(T t)
{
   std::stringstream ss;
   ss<<t;
   return ss.str();
}