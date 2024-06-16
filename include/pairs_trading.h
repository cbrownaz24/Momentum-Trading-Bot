#ifndef PAIRS_TRADING_H
#define PAIRS_TRADING_H

#include <vector>
#include <string>
#include <utility>

std::pair<std::vector<double>, std::vector<double>> fetchPairData(const std::string& filename1, const std::string& filename2);
std::vector<int> pairsTradingStrategy(const std::vector<double>& prices1, const std::vector<double>& prices2, double zScoreEntry, double zScoreExit);

#endif // PAIRS_TRADING_H
