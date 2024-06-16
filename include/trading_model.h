#ifndef TRADING_MODEL_H
#define TRADING_MODEL_H

#include <vector>
#include "..\dlib\svm\svm_threaded.h"

typedef dlib::matrix<double, 3, 1> sample_type;

class TradingModel {
public:
    TradingModel();
    void trainModel(const std::vector<sample_type>& samples, const std::vector<double>& labels);
    double predict(const sample_type& sample) const;

private:
    dlib::decision_function<dlib::radial_basis_kernel<sample_type>> df;
};

#endif // TRADING_MODEL_H
