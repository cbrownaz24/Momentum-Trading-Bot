#ifndef DATA_FETCHER_H
#define DATA_FETCHER_H

#include <vector>
#include <string>

struct StockData {
    std::string date;
    double close;
    double open;
    double high;
    double low;
    double volume;
};

std::vector<StockData> fetchData(const std::string& filename);

#endif // DATA_FETCHER_H
