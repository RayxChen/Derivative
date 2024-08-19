#ifndef OPTION_PRICING_HPP
#define OPTION_PRICING_HPP

#include <vector>

enum OptionType { Call, Put };
enum ExerciseType { European, American };
enum BarrierType { NoBarrier, UpAndIn, UpAndOut, DownAndIn, DownAndOut };

class OptionPricing {
public:
    // Constructor
    OptionPricing(double S0, double K, double r, double T, double sigma, int N, OptionType optType, ExerciseType exType, BarrierType barType = NoBarrier, double barrierLevel = 0.0, const std::vector<std::pair<double, double>>& dividends = {});

    // Method to calculate option price
    double calculateOptionPrice() const;

private:
    double S0;            // Initial stock price
    double K;             // Strike price
    double r;             // Risk-free rate
    double T;             // Time to maturity
    double sigma;         // Volatility
    int N;                // Number of time steps
    OptionType optType;   // Option type (Call or Put)
    ExerciseType exType;  // Exercise type (European or American)
    BarrierType barType;  // Barrier type (NoBarrier, UpAndIn, etc.)
    double barrierLevel;  // Barrier level
    std::vector<std::pair<double, double>> dividends; // Vector of (time, amount) pairs for dividends

    double calculateUpFactor() const;
    double calculateDownFactor() const;
    double calculateRiskNeutralProbability(double u, double d) const;
    double payoff(double stockPrice) const;
    bool isBarrierBreached(double stockPrice) const;
    double adjustForDividend(double stockPrice, double time) const;
};

#endif // OPTION_PRICING_HPP
