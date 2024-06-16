#include "data_fetcher.h"
#include "logger.h"
#include <fstream>
#include <sstream>

std::vector<StockData> fetchData(const std::string& filename) {
    std::vector<StockData> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::error("Failed to open file: " + filename);
        return data;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, open, high, low, close, volume;
        std::getline(ss, date, ',');
        std::getline(ss, open, ',');
        std::getline(ss, high, ',');
        std::getline(ss, low, ',');
        std::getline(ss, close, ',');
        std::getline(ss, volume, ',');
        data.push_back({date, std::stod(close), std::stod(open), std::stod(high), std::stod(low), std::stod(volume)});
    }
    Logger::log("Data fetched from file: " + filename);
    return data;
}
