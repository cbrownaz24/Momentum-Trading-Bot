#include "trading_model.h"
#include "logger.h"
#include <dlib/svm_threaded.h>
#include <dlib/data_io.h>

using namespace dlib;

TradingModel::TradingModel() {
    try {
        dlib::deserialize("ml_model.dat") >> df;
        Logger::log("Model loaded from ml_model.dat.");
    } catch (const std::exception& e) {
        Logger::error("Failed to load model: " + std::string(e.what()));
    }
}

void TradingModel::trainModel(const std::vector<sample_type>& samples, const std::vector<double>& labels) {
    try {
        typedef radial_basis_kernel<sample_type> kernel_type;
        dlib::krr_trainer<kernel_type> trainer;
        df = trainer.train(samples, labels);
        dlib::serialize("ml_model.dat") << df;
        Logger::log("Model trained and saved to ml_model.dat.");
    } catch (const std::exception& e) {
        Logger::error("Failed to train model: " + std::string(e.what()));
    }
}

double TradingModel::predict(const sample_type& sample) const {
    try {
        return df(sample);
    } catch (const std::exception& e) {
        Logger::error("Prediction error: " + std::string(e.what()));
        return 0.0;
    }
}

