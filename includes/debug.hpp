#pragma once

#include "common.hpp"

#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_RESET   "\033[0m"

#define DEBUG_INFO(msg) \
    std::cout << COLOR_GREEN << "[INFO] " << __FILE__ << ":" << __LINE__ << " - " << msg << COLOR_RESET << std::endl;

#define DEBUG_ERROR(msg) \
    std::cerr << COLOR_RED << "[ERROR] " << __FILE__ << ":" << __LINE__ << " - " << msg << COLOR_RESET << std::endl;

#define DEBUG_WARN(msg) \
    std::cout << COLOR_YELLOW << "[WARN] " << __FILE__ << ":" << __LINE__ << " - " << msg << COLOR_RESET << std::endl;

namespace DEBUG {
}