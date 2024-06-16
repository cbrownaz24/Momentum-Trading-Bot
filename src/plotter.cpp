#include "plotter.h"
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

void plotData(const std::vector<StockData>& data, const BollingerBands& bands, const MomentumSignal& signal) {
    std::vector<double> dates;
    std::vector<double> closes;
    std::vector<double> upperBand;
    std::vector<double> lowerBand;
    std::vector<double> sma;
    std::vector<int> positions;

    for (const auto& d : data) {
        dates.push_back(std::stod(d.date));
        closes.push_back(d.close);
    }

    upperBand.assign(bands.upperBand.begin(), bands.upperBand.end());
    lowerBand.assign(bands.lowerBand.begin(), bands.lowerBand.end());
    sma.assign(bands.sma.begin(), bands.sma.end());
    positions.assign(signal.positions.begin(), signal.positions.end());

    plt::figure_size(1200, 780);
    plt::named_plot("Close", dates, closes, "k-");
    plt::named_plot("Upper Band", dates, upperBand, "r--");
    plt::named_plot("Lower Band", dates, lowerBand, "b--");
    plt::named_plot("SMA", dates, sma, "g-");

    for (size_t i = 0; i < dates.size(); ++i) {
        if (positions[i] == 1) {
            plt::annotate("Buy", dates[i], closes[i], "green");
        } else if (positions[i] == -1) {
            plt::annotate("Sell", dates[i], closes[i], "red");
        }
    }

    plt::legend();
    plt::show();
}
