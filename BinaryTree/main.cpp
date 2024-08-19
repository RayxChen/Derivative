#include <iostream>
#include "OptionPricing.hpp"

int main() {
    // Define parameters
    double S0 = 90.0;   // Initial stock price
    double K = 100.0;    // Strike price
    double r = 0.05;     // Risk-free rate
    double T = 1.0;      // Time to maturity
    double sigma = 0.2;  // Volatility
    int N = 10000;         // Number of time steps
    double barrierLevel = 110.0;  // Barrier level for barrier options

    // Define dividends as pairs of (time, amount)
    std::vector<std::pair<double, double>> dividends = { {0.25, 2.0}, {0.5, 2.0}, {0.75, 2.0} };

    // Create OptionPricing objects for different scenarios
    OptionPricing EuropeanCall(S0, K, r, T, sigma, N, Call, European, NoBarrier, 0.0, dividends);
    OptionPricing EuropeanPut(S0, K, r, T, sigma, N, Put, European, NoBarrier, 0.0, dividends);
    OptionPricing AmericanCall(S0, K, r, T, sigma, N, Call, American, NoBarrier, 0.0, dividends);
    OptionPricing AmericanPut(S0, K, r, T, sigma, N, Put, American, NoBarrier, 0.0, dividends);
    OptionPricing UpAndOutCall(S0, K, r, T, sigma, N, Call, European, UpAndOut, barrierLevel, dividends);
    OptionPricing DownAndOutPut(S0, K, r, T, sigma, N, Put, European, DownAndOut, barrierLevel, dividends);
    OptionPricing UpAndInCall(S0, K, r, T, sigma, N, Call, European, UpAndIn, barrierLevel, dividends);
    OptionPricing DownAndInPut(S0, K, r, T, sigma, N, Put, European, DownAndIn, barrierLevel, dividends);

    // Calculate and display option prices
    std::cout << "European Call Option Price with Dividends: " << EuropeanCall.calculateOptionPrice() << std::endl;
    std::cout << "European Put Option Price with Dividends: " << EuropeanPut.calculateOptionPrice() << std::endl;
    std::cout << "American Call Option Price with Dividends: " << AmericanCall.calculateOptionPrice() << std::endl;
    std::cout << "American Put Option Price with Dividends: " << AmericanPut.calculateOptionPrice() << std::endl;
    std::cout << "Up-and-Out Call Option Price with Dividends: " << UpAndOutCall.calculateOptionPrice() << std::endl;
    std::cout << "Down-and-Out Put Option Price with Dividends: " << DownAndOutPut.calculateOptionPrice() << std::endl;
    std::cout << "Up-and-In Call Option Price with Dividends: " << UpAndInCall.calculateOptionPrice() << std::endl;
    std::cout << "Down-and-In Put Option Price with Dividends: " << DownAndInPut.calculateOptionPrice() << std::endl;

    return 0;
}
