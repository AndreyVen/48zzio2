#ifndef VENDETTA_BUDGET_H
#define VENDETTA_BUDGET_H

#include <amount.h>
#include <string>

class CTransaction;
class CValidationState;

namespace vendetta {

/** Required budget payment validity checks */
bool CheckBudgetTransaction(const int nHeight, const CTransaction& tx, CValidationState& state);

class BudgetParams
{

private:
    explicit BudgetParams(std::string strNetwork);

    std::string founderAddress;


public:

    static BudgetParams* Get();

    static void GetBlockRewards(int nBlockHeight,
                                CAmount& nBlockReward,
                                CAmount& nFounderPayment);


    std::string GetFounderAddress() const { return founderAddress; }

    static const int nBlocksPerPeriod = 43200;
};

BudgetParams& Budget();

}

#endif //VENDETTA_BUDGET_H

