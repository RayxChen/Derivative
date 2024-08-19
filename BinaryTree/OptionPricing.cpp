#include "OptionPricing.hpp"
#include <cmath>
#include <algorithm>

// Constructor
OptionPricing::OptionPricing(double S0, double K, double r, double T, double sigma, int N, OptionType optType, ExerciseType exType, BarrierType barType, double barrierLevel, const std::vector<std::pair<double, double>>& dividends)
    : S0(S0), K(K), r(r), T(T), sigma(sigma), N(N), optType(optType), exType(exType), barType(barType), barrierLevel(barrierLevel), dividends(dividends) {}

// Method to calculate option price
double OptionPricing::calculateOptionPrice() const {
    double dt = T / N;                 // Time step
    double u = calculateUpFactor();    // Up factor
    double d = calculateDownFactor();  // Down factor
    double p = calculateRiskNeutralProbability(u, d);  // Risk-neutral probability
    double discount = std::exp(-r * dt);    // Discount factor

    // Create the stock price tree (initialize at maturity)
    std::vector<double> stockPrices(N + 1);
    for (int i = 0; i <= N; ++i) {
        stockPrices[i] = S0 * std::pow(u, N - i) * std::pow(d, i);
        stockPrices[i] = adjustForDividend(stockPrices[i], T);  // Adjust for dividends at maturity
    }

    // Create the option value tree
    std::vector<double> optionValues(N + 1);
    for (int i = 0; i <= N; ++i) {
        // Check if the barrier condition is met at maturity
        if (isBarrierBreached(stockPrices[i])) {
            optionValues[i] = 0.0;  // If breached, the option may become worthless
        } else {
            optionValues[i] = payoff(stockPrices[i]);  // Payoff at maturity
        }
    }

    // Step back through the tree
    for (int j = N - 1; j >= 0; --j) {
        double currentTime = j * dt;  // Current time
        for (int i = 0; i <= j; ++i) {
            // Update stock price for the current node by moving backwards
            stockPrices[i] = stockPrices[i] / u;  // Moving backwards, so dividing by 'u'
            
            // Check if the barrier condition is met
            bool barrierBreached = isBarrierBreached(stockPrices[i]);

            if (barrierBreached) {
                if (barType == DownAndOut || barType == UpAndOut) {
                    optionValues[i] = 0.0;  // If breached, the option becomes worthless for Out options
                } else if (barType == DownAndIn || barType == UpAndIn) {
                    // Option is active (no need to nullify); continue with normal option pricing
                    optionValues[i] = discount * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);
                    if (exType == American) {
                        optionValues[i] = std::max(optionValues[i], payoff(stockPrices[i]));
                    }
                }
            } else {
                // No barrier breach, continue normal option pricing
                optionValues[i] = discount * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);
                if (exType == American) {
                    optionValues[i] = std::max(optionValues[i], payoff(stockPrices[i]));
                }
            }
        }
    }

    return optionValues[0];  // Option value at t=0
}

// Private methods
double OptionPricing::calculateUpFactor() const {
    double dt = T / N;
    return std::exp(sigma * std::sqrt(dt));
}

double OptionPricing::calculateDownFactor() const {
    return 1.0 / calculateUpFactor();
}

double OptionPricing::calculateRiskNeutralProbability(double u, double d) const {
    double dt = T / N;
    return (std::exp(r * dt) - d) / (u - d);
}

double OptionPricing::payoff(double stockPrice) const {
    if (optType == Call) {
        return std::max(0.0, stockPrice - K);
    } else { // Put
        return std::max(0.0, K - stockPrice);
    }
}

bool OptionPricing::isBarrierBreached(double stockPrice) const {
    switch (barType) {
        case UpAndIn:
            return stockPrice >= barrierLevel;
        case UpAndOut:
            return stockPrice >= barrierLevel;
        case DownAndIn:
            return stockPrice <= barrierLevel;
        case DownAndOut:
            return stockPrice <= barrierLevel;
        default:
            return false;  // NoBarrier case
    }
}

double OptionPricing::adjustForDividend(double stockPrice, double time) const {
    for (const auto& dividend : dividends) {
        if (time == dividend.first) {
            stockPrice -= dividend.second;
        }
    }
    return stockPrice;
}
