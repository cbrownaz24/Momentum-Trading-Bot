#include "changepoint_detection.h"
#include "logger.h"
#include <numeric>
#include <cmath>
#include <iostream>

std::vector<int> detectChangepoints(const std::vector<double>& data) {
    std::vector<int> changepoints;
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double threshold = 0.05 * mean;
    for (int i = 1; i < data.size(); ++i) {
        if (std::abs(data[i] - data[i - 1]) > threshold) {
            changepoints.push_back(i);
        }
    }

    if (changepoints.empty()) {
        Logger::error("No changepoints detected.");
    } else {
        Logger::log("Changepoints detected.");
    }

    return changepoints;
}
