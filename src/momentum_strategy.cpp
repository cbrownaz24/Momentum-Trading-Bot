#include "momentum_strategy.h"
#include "logger.h"

MomentumSignal momentumStrategy(const std::vector<double>& prices, const BollingerBands& bands) {
    MomentumSignal signal;
    for (int i = 0; i < prices.size(); ++i) {
        if (i < bands.upperBand.size()) {
            if (prices[i] > bands.upperBand[i]) {
                signal.positions.push_back(-1); // Sell signal
            } else if (prices[i] < bands.lowerBand[i]) {
                signal.positions.push_back(1); // Buy signal
            } else {
                signal.positions.push_back(0); // Hold
            }
        } else {
            signal.positions.push_back(0); // Hold
        }
    }
    if (signal.positions.empty()) {
        Logger::error("Failed to generate momentum signals.");
    } else {
        Logger::log("Momentum signals generated.");
    }
    return signal;
}
