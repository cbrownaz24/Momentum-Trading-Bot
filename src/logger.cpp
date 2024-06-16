#include "logger.h"
#include <iostream>
#include <fstream>

void Logger::log(const std::string& message) {
    std::ofstream log_file("log.txt", std::ios_base::out | std::ios_base::app);
    log_file << "INFO: " << message << std::endl;
    std::cout << "INFO: " << message << std::endl;
}

void Logger::error(const std::string& message) {
    std::ofstream log_file("log.txt", std::ios_base::out | std::ios_base::app);
    log_file << "ERROR: " << message << std::endl;
    std::cerr << "ERROR: " << message << std::endl;
}
