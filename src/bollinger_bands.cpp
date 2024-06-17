#include "../include/bollinger_bands.h"
#include "../include/logger.h"
#include <cmath>
#include <numeric>

BollingerBands computeBollingerBands(const std::vector<double>& prices, int window) {
    BollingerBands bands;
    double sum = 0.0;
    for (int i = 0; i < prices.size(); ++i) {
        sum += prices[i];
        if (i >= window) {
            sum -= prices[i - window];
        }
        if (i >= window - 1) {
            double mean = sum / window;
            bands.sma.push_back(mean);
            double squared_diff_sum = 0.0;
            for (int j = i - window + 1; j <= i; ++j) {
                squared_diff_sum += std::pow(prices[j] - mean, 2);
            }
            double std_dev = std::sqrt(squared_diff_sum / window);
            bands.upperBand.push_back(mean + 2 * std_dev);
            bands.lowerBand.push_back(mean - 2 * std_dev);
        }
    }
    if (bands.sma.empty() || bands.upperBand.empty() || bands.lowerBand.empty()) {
        Logger::error("Failed to compute Bollinger Bands.");
    } else {
        Logger::log("Bollinger Bands computed.");
    }
    return bands;
}
