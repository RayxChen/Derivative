#ifndef PATH_DEPENDENT_BARRIER_OPTION_H
#define PATH_DEPENDENT_BARRIER_OPTION_H

#include "PathDependent.h"
#include "PayOffBridge.h"
#include "Arrays.h"
#include <vector>

class PathDependentBarrier : public PathDependent
{
public:
    enum BarrierType { KnockOut, KnockIn };

    PathDependentBarrier(const MJArray& LookAtTimes_,
                               double Expiry_,
                               const PayOffBridge& ThePayOff_,
                               double Barrier_,
                               BarrierType BarrierType_);

    virtual unsigned long MaxNumberOfCashFlows() const override;
    virtual MJArray PossibleCashFlowTimes() const override;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const override;
    virtual ~PathDependentBarrier() {}
    virtual PathDependent* clone() const override;

private:
    double Barrier;
    PayOffBridge ThePayOff;
    BarrierType TheBarrierType;
};

#endif
