#include "../include/monte_carlo.h"
#include "../include/logger.h"
#include <random>
#include <cmath>
#include <iostream>

std::vector<std::vector<double>> monteCarloSimulation(const std::vector<double>& returns, int num_simulations, int num_days) {
    std::vector<std::vector<double>> simulations;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1);

    for (int i = 0; i < num_simulations; ++i) {
        std::vector<double> simulation;
        double last_price = returns.back();
        for (int j = 0; j < num_days; ++j) {
            double shock = d(gen) * std::sqrt(1.0 / num_days);
            double drift = (0.1 - 0.5 * 0.2 * 0.2) * (1.0 / num_days);
            double price = last_price * std::exp(drift + shock);
            simulation.push_back(price);
            last_price = price;
        }
        simulations.push_back(simulation);
    }

    if (simulations.empty()) {
        Logger::error("Monte Carlo simulation failed to generate results.");
    } else {
        Logger::log("Monte Carlo simulations generated.");
    }

    return simulations;
}
