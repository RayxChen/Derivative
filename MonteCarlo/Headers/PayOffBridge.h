#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H
#include "PayOff.h"


// bridge pattern:  a class that does nothing except store a pointer
// to an option pay-off and takes care of memory handling.

class PayOffBridge
{
public:
    PayOffBridge(const PayOffBridge& original);
    PayOffBridge(const PayOff& innerPayOff);
    inline double operator()(double Spot) const;
    ~PayOffBridge();
    PayOffBridge& operator=(const PayOffBridge& original);

private:
    PayOff* ThePayOffPtr;
};

inline double PayOffBridge::operator()(double Spot) const
{
    return ThePayOffPtr->operator ()(Spot);
}

#endif