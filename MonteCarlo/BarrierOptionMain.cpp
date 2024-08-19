#include <iostream>
#include "./Headers/SimulationSetup.h"
#include "./Headers/PayOff.h"
#include "./Headers/Arrays.h"
#include "./Headers/Random.h"
#include "./Headers/ConvergenceTable.h"
#include "./Headers/MCStatistics.h"
#include "./Headers/ExoticBSEngine.h"
#include "./Headers/PathDependentBarrier.h"
#include "./Headers/AntiThetic.h"
#include "./Headers/ParkMiller.h"

int main() {
    SimulationParameters params;
    std::ofstream logFile;
    
    // Initialize simulation parameters
    if (!SimulationSetup::initializeSimulationParameters(params, logFile, "./log.txt")) {
        std::cerr << "Failed to initialize simulation parameters." << std::endl;
        return 1;  // Exit with error code if initialization fails
    }

    // Check if the selected option type is a Barrier option
    if (params.optionType != Barrier) {
        std::cerr << "This simulation is set up only for Barrier options." << std::endl;
        return 1;  // Exit if not set up for a Barrier option
    }

    // Set up pricing components
    PayOffCall thePayOff(params.strike);
    MJArray times(params.numberOfDates);
    for (unsigned long i = 0; i < params.numberOfDates; i++) {
        times[i] = (i + 1.0) * params.expiry / params.numberOfDates;
    }

    // Create model parameters
    ParametersConstant VolParam(params.vol), rParam(params.r), dParam(params.d);

    // Set up the Barrier option with the payoff and the monitoring times
    PathDependentBarrier theOption(times, params.expiry, thePayOff, params.barrier, PathDependentBarrier::KnockOut);

    // Set up the statistics gathering
    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);

    // Set up the random number generator
    RandomParkMiller generator(params.numberOfDates);
    AntiThetic GenTwo(generator);

    // Set up the Monte Carlo simulation engine
    ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, params.spot);

    // Perform the simulation
    theEngine.DoSimulation(gathererTwo, params.numberOfPaths);

    // Retrieve and log the results
    std::vector<std::vector<double>> results = gathererTwo.GetResultsSoFar();
    logFile << "For the Barrier option price, the results are:\n";
    for (unsigned long i = 0; i < results.size(); i++) {
        for (unsigned long j = 0; j < results[i].size(); j++)
            logFile << results[i][j] << " ";
        logFile << "\n";
    }

    logFile.close();
    std::cout << "Simulation complete. Results logged to file." << std::endl;

    // Keep the console window open until the user is ready to close it
    std::cout << "Press enter to exit.";
    std::cin.ignore();
    std::cin.get();
    
    return 0;
}
