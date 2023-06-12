#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <sstream>

#include "Node.hpp"

namespace Project
{
inline bool isNumeric(std::string str)
{
    for(int i = 0; i < str.length(); i++)
        if(!isdigit(str[i]))
            return false;
    return true;
}

inline int toInt(std::string str)
{
    std::stringstream conversion;
    int res;
    conversion << str;
    conversion >> res;
    return res;
}

}  // namespace Project

#endif  // FUNCTIONS_HPP
