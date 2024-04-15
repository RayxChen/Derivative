// SimulationSetup.h
#ifndef SIMULATION_SETUP_H
#define SIMULATION_SETUP_H

#include <iostream>
#include <fstream>
#include <string>

enum OptionType {
    European,
    Asian,
    Barrier,
    American,
    Lookback,
    Digital,
    Bermuda
};

struct SimulationParameters {
    double expiry, strike, spot, vol, r, d, barrier;
    unsigned long numberOfPaths;
    unsigned numberOfDates;
    OptionType optionType;
};

class SimulationSetup {
public:
    static bool initializeSimulationParameters(SimulationParameters& params, std::ofstream& logFile, const std::string& logFilePath);
    static std::string getOptionTypeName(OptionType type);
};

#endif // SIMULATION_SETUP_H
