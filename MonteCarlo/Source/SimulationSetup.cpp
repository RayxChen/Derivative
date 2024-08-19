// SimulationSetup.cpp
#include "../Headers/SimulationSetup.h"

bool SimulationSetup::initializeSimulationParameters(SimulationParameters& params, std::ofstream& logFile, const std::string& logFilePath) {
    std::cout << "Select option type (0=European, 1=Asian, 2=Barrier, 3=American, 4=Lookback, 5=Digital, 6=Bermuda): ";
    int typeInput;
    std::cin >> typeInput;
    params.optionType = static_cast<OptionType>(typeInput);

    std::cout << "\nEnter expiry: ";
    std::cin >> params.expiry;
    std::cout << "\nEnter strike: ";
    std::cin >> params.strike;
    std::cout << "\nEnter spot: ";
    std::cin >> params.spot;
    std::cout << "\nEnter volatility: ";
    std::cin >> params.vol;
    std::cout << "\nEnter risk-free rate (r): ";
    std::cin >> params.r;
    std::cout << "\nEnter dividend rate (d): ";
    std::cin >> params.d;

    if (params.optionType == Barrier) {
        std::cout << "\nEnter barrier level: ";
        std::cin >> params.barrier;
    }
    if (params.optionType != European && params.optionType != Digital) {
        std::cout << "\nEnter number of dates for monitoring";
        std::cin >> params.numberOfDates;
    }

    std::cout << "\nEnter number of paths: ";
    std::cin >> params.numberOfPaths;

    logFile.open(logFilePath);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return false;
    }

    logFile << "Simulation Parameters:\n";
    logFile << "Option Type: " << getOptionTypeName(params.optionType) << "\n";
    logFile << "Expiry: " << params.expiry << "\n";
    logFile << "Strike: " << params.strike << "\n";
    logFile << "Spot: " << params.spot << "\n";
    logFile << "Volatility: " << params.vol << "\n";
    logFile << "Risk-free rate: " << params.r << "\n";
    logFile << "Dividend rate: " << params.d << "\n";
    if (params.optionType == Barrier) {
        logFile << "Barrier level: " << params.barrier << "\n";
    }
    if (params.optionType != European && params.optionType != Digital) {
        logFile << "Number of monitoring dates: " << params.numberOfDates << "\n";
    }
    logFile << "Number of paths: " << params.numberOfPaths << "\n\n";
    return true;
}

std::string SimulationSetup::getOptionTypeName(OptionType type) {
    switch (type) {
        case European: return "European";
        case Asian: return "Asian";
        case Barrier: return "Barrier";
        case American: return "American";
        case Lookback: return "Lookback";
        case Digital: return "Digital";
        case Bermuda: return "Bermuda";
        default: return "Unknown";
    }
}
