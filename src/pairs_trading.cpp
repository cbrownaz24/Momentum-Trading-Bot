#include "../include/pairs_trading.h"
#include "../include/logger.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>

// Function to fetch data for a pair of stocks
std::pair<std::vector<double>, std::vector<double>> fetchPairData(const std::string& filename1, const std::string& filename2) {
    std::vector<double> data1, data2;
    std::ifstream file1(filename1), file2(filename2);
    std::string line;
    while (std::getline(file1, line)) {
        std::stringstream ss(line);
        std::string date, close;
        std::getline(ss, date, ',');
        std::getline(ss, close, ',');
        data1.push_back(std::stod(close));
    }
    while (std::getline(file2, line)) {
        std::stringstream ss(line);
        std::string date, close;
        std::getline(ss, date, ',');
        std::getline(ss, close, ',');
        data2.push_back(std::stod(close));
    }
    Logger::log("Pair data fetched from files: " + filename1 + " and " + filename2);
    return std::make_pair(data1, data2);
}

// Function to implement the pairs trading strategy
std::vector<int> pairsTradingStrategy(const std::vector<double>& prices1, const std::vector<double>& prices2, double zScoreEntry, double zScoreExit) {
    std::vector<int> signals(prices1.size(), 0);
    std::vector<double> ratios(prices1.size(), 0.0);
    for (size_t i = 0; i < prices1.size(); ++i) {
        ratios[i] = prices1[i] / prices2[i];
    }
    double mean = std::accumulate(ratios.begin(), ratios.end(), 0.0) / ratios.size();
    double sq_sum = std::inner_product(ratios.begin(), ratios.end(), ratios.begin(), 0.0);
    double std_dev = std::sqrt(sq_sum / ratios.size() - mean * mean);
    for (size_t i = 0; i < ratios.size(); ++i) {
        double zScore = (ratios[i] - mean) / std_dev;
        if (zScore > zScoreEntry) {
            signals[i] = -1; // Short the first stock and long the second
        } else if (zScore < -zScoreEntry) {
            signals[i] = 1;  // Long the first stock and short the second
        } else if (std::abs(zScore) < zScoreExit) {
            signals[i] = 0;  // Exit any open positions
        }
    }
    Logger::log("Pairs trading strategy signals generated.");
    return signals;
}
