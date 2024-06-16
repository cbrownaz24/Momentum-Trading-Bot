#include <iostream>
#include <vector>
#include "data_fetcher.h"
#include "bollinger_bands.h"
#include "momentum_strategy.h"
#include "trading_model.h"
#include "monte_carlo.h"
#include "changepoint_detection.h"
#include "plotter.h"
#include "pairs_trading.h"
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
        auto pairData = fetchPairData(correlatedPairs[0].
