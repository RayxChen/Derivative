#include "../Headers/PayOff.h"
#include <algorithm>
#include <cmath>

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_) {}

double PayOffCall::operator () (double Spot) const
{
    return std::max(Spot-Strike,0.0);
}

PayOff* PayOffCall::clone() const 
{
    return new PayOffCall(*this);
}

double PayOffPut::operator()(double Spot) const
{
    return std::max(Strike-Spot,0.0);
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}