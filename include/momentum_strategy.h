#ifndef MOMENTUM_STRATEGY_H
#define MOMENTUM_STRATEGY_H

#include <vector>
#include "bollinger_bands.h"

struct MomentumSignal {
    std::vector<int> positions;
};

MomentumSignal momentumStrategy(const std::vector<double>& prices, const BollingerBands& bands);

#endif // MOMENTUM_STRATEGY_H