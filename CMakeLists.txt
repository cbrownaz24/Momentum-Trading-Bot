cmake_minimum_required(VERSION 3.10)
project(QuantLibExtension)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(QuantLibExtension
    main.cpp
    src/data_fetcher.cpp
    src/bollinger_bands.cpp
    src/momentum_strategy.cpp
    src/trading_model.cpp
    src/monte_carlo.cpp
    src/changepoint_detection.cpp
    src/plotter.cpp
    src/pairs_trading.cpp
    src/logger.cpp
)

find_package(Eigen3 REQUIRED)
find_package(Dlib REQUIRED)
find_package(Boost REQUIRED)
find_package(PythonLibs REQUIRED)

target_link_libraries(QuantLibExtension
    Eigen3::Eigen
    dlib::dlib
    Boost::Boost
    ${PYTHON_LIBRARIES}
)
