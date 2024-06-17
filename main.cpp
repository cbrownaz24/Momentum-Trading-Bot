#include <iostream>
#include <vector>
#include "data_fetcher.h"
#include "bollinger_bands.h"
#include "momentum_strategy.h"
#include "trading_model.h"
#include "monte_carlo.h"
#include "changepoint_detection.h"
#include "pairs_trading.h"
#include "logger.h"
#include "correlation.h"

int main() {
    // List of stock tickers to analyze
    std::vector<std::string> tickers = {"AAPL", "GOOG", "MSFT", "AMZN", "FB"};

    // Find correlated pairs with a threshold of 0.8
    auto correlatedPairs = findCorrelatedPairs(tickers, 0.8);

    // Print correlated pairs
    for (const auto& pair : correlatedPairs) {
        std::cout << "Correlated Pair: " << pair.first << " - " << pair.second << std::endl;
    }

    // Fetch data for a specific pair and implement pairs trading strategy
    if (!correlatedPairs.empty()) {
        auto pairData = fetchPairData(correlatedPairs[0].first + ".csv", correlatedPairs[0].second + ".csv");
        auto pairSignals = pairsTradingStrategy(pairData.first, pairData.second, 2.0, 0.5);

        // Output pair trading signals
        for (size_t i = 0; i < pairSignals.size(); ++i) {
            std::cout << "Day " << i << ": Signal " << pairSignals[i] << std::endl;
        }
    }

    // Fetch data for single stock analysis
    auto data = fetchData("stock_data.csv");

    std::vector<double> prices;
    for (const auto& d : data) {
        prices.push_back(d.close);
    }

    // Compute Bollinger Bands
    auto bands = computeBollingerBands(prices, 20);

    // Generate momentum signals
    auto signal = momentumStrategy(prices, bands);

    // Prepare data for machine learning model
    std::vector<sample_type> samples;
    std::vector<double> labels;
    for (size_t i = 1; i < prices.size(); ++i) {
        sample_type sample;
        sample(0) = prices[i] - prices[i - 1];
        sample(1) = bands.upperBand[i] - bands.lowerBand[i];
        sample(2) = prices[i];
        samples.push_back(sample);
        labels.push_back(prices[i] > prices[i - 1] ? 1 : 0);
    }

    // Train the trading model
    TradingModel model;
    model.trainModel(samples, labels);

    // Monte Carlo Simulation
    auto simulations = monteCarloSimulation(prices, 1000, 252);

    // Detect changepoints
    auto changepoints = detectChangepoints(prices);

    // Output results
    for (const auto& sim : simulations) {
        for (const auto& price : sim) {
            std::cout << price << " ";
        }
        std::cout << std::endl;
    }

    for (const auto& cp : changepoints) {
        std::cout << "Changepoint at index: " << cp << std::endl;
    }

    return 0;
}
