#include "../include/correlation.h"
#include "../include/data_fetcher.h"
#include "../include/logger.h"
#include <Eigen/Dense>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iostream>

using Eigen::MatrixXd;

// Helper function to calculate correlation coefficient between two vectors
double calculateCorrelation(const std::vector<double>& x, const std::vector<double>& y) {
    double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

    double numerator = 0.0;
    double denominator_x = 0.0;
    double denominator_y = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
        denominator_x += std::pow(x[i] - mean_x, 2);
        denominator_y += std::pow(y[i] - mean_y, 2);
    }

    double denominator = std::sqrt(denominator_x) * std::sqrt(denominator_y);
    return numerator / denominator;
}

// Function to find correlated pairs of stocks
std::vector<std::pair<std::string, std::string>> findCorrelatedPairs(const std::vector<std::string>& tickers, double threshold) {
    size_t n = tickers.size();
    std::vector<std::pair<std::string, std::string>> correlatedPairs;

    // Fetch data for all tickers
    std::vector<std::vector<double>> allPrices;
    for (const auto& ticker : tickers) {
        auto data = fetchData(ticker + ".csv");
        std::vector<double> prices;
        for (const auto& d : data) {
            prices.push_back(d.close);
        }
        allPrices.push_back(prices);
    }

    // Calculate correlation matrix
    MatrixXd correlationMatrix = MatrixXd::Zero(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            double correlation = calculateCorrelation(allPrices[i], allPrices[j]);
            correlationMatrix(i, j) = correlation;
            correlationMatrix(j, i) = correlation;
        }
    }

    // Select pairs with correlation above the threshold
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (correlationMatrix(i, j) > threshold) {
                correlatedPairs.push_back({tickers[i], tickers[j]});
            }
        }
    }

    Logger::log("Correlated pairs identified.");
    return correlatedPairs;
}
