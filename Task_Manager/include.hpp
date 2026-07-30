// include paths
# pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept> 

namespace Term {
    constexpr const char* RESET  = "\033[0m";
    constexpr const char* RED    = "\033[1;31m";
    constexpr const char* GREEN  = "\033[1;32m";
    constexpr const char* YELLOW = "\033[1;33m";
    constexpr const char* GRAY   = "\033[1;37m";
} // namespace term

inline std::string paint(const std::string& text, const char* term){
    return std::string(term) + text + Term::RESET;
}   
