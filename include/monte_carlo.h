#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>

std::vector<std::vector<double>> monteCarloSimulation(const std::vector<double>& returns, int num_simulations, int num_days);

#endif // MONTE_CARLO_H
