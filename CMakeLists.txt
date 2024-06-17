cmake_minimum_required(VERSION 3.10)
project(MomentumProject)

set(CMAKE_CXX_STANDARD 17)

# Include the local Eigen and Dlib directories
include_directories(${CMAKE_SOURCE_DIR}/eigen-3.4.0)
# include_directories(${CMAKE_SOURCE_DIR}/dlib)

include_directories(include)

# Verify that the required source files exist
file(GLOB_RECURSE SRC_FILES 
    "src/data_fetcher.cpp"
    "src/bollinger_bands.cpp"
    "src/momentum_strategy.cpp"
    "src/trading_model.cpp"
    "src/monte_carlo.cpp"
    "src/changepoint_detection.cpp"
    "src/pairs_trading.cpp"
    "src/logger.cpp"
    "src/correlation.cpp"
)

if (NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in src directory.")
endif()

add_executable(MomentumProject main.cpp ${SRC_FILES})

find_package(PythonLibs REQUIRED)

# Add the Dlib source directory
add_subdirectory(dlib)

target_link_libraries(MomentumProject
    dlib
    ${PYTHON_LIBRARIES}
)
