#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>
#include "data_fetcher.h"
#include "bollinger_bands.h"
#include "momentum_strategy.h"

void plotData(const std::vector<StockData>& data, const BollingerBands& bands, const MomentumSignal& signal);

#endif // PLOTTER_H
