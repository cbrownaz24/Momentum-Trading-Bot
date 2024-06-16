#ifndef BOLLINGER_BANDS_H
#define BOLLINGER_BANDS_H

#include <vector>

struct BollingerBands {
    std::vector<double> upperBand;
    std::vector<double> lowerBand;
    std::vector<double> sma;
};

BollingerBands computeBollingerBands(const std::vector<double>& prices, int window);

#endif // BOLLINGER_BANDS_H