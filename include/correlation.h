#ifndef CORRELATION_H
#define CORRELATION_H

#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::string, std::string>> findCorrelatedPairs(const std::vector<std::string>& tickers, double threshold);

#endif // CORRELATION_H
