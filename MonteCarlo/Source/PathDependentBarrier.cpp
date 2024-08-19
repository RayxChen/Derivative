#include "../Headers/PathDependentBarrier.h"
#include "../Headers/Arrays.h"
#include <cmath>

PathDependentBarrier::PathDependentBarrier(const MJArray& LookAtTimes_,
                                                       double Expiry_,
                                                       const PayOffBridge& ThePayOff_,
                                                       double Barrier_,
                                                       BarrierType BarrierType_)
: PathDependent(LookAtTimes_), ThePayOff(ThePayOff_), Barrier(Barrier_), TheBarrierType(BarrierType_)
{
}

unsigned long PathDependentBarrier::MaxNumberOfCashFlows() const
{
    return 1UL; // At most one cash flow (at expiry)
}

MJArray PathDependentBarrier::PossibleCashFlowTimes() const
{
    MJArray tmp(1);
    tmp[0] = GetLookAtTimes()[GetLookAtTimes().size() - 1];
    return tmp;
}

unsigned long PathDependentBarrier::CashFlows(const MJArray& SpotValues,
                                                    std::vector<CashFlow>& GeneratedFlows) const
{
    bool barrierHit = false;
    size_t numTimes = GetLookAtTimes().size();
    for (size_t i = 0; i < numTimes; ++i) {
        if ((TheBarrierType == KnockOut && SpotValues[i] >= Barrier) ||
            (TheBarrierType == KnockIn && SpotValues[i] >= Barrier)) {
            barrierHit = true;
            break;
        }
    }

    if ((TheBarrierType == KnockOut && !barrierHit) || (TheBarrierType == KnockIn && barrierHit)) {
        GeneratedFlows[0].TimeIndex = 0;
        GeneratedFlows[0].Amount = ThePayOff(SpotValues[numTimes - 1]);
    } else {
        GeneratedFlows[0].Amount = 0.0;  // No payout if conditions are not met
    }

    return 1UL; // One cash flow
}

PathDependent* PathDependentBarrier::clone() const
{
    return new PathDependentBarrier(*this);
}

