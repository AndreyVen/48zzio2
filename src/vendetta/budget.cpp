#include <vendetta/budget.h>

#include <consensus/validation.h>
#include <key_io.h>

namespace vendetta {
bool CheckBudgetTransaction(const int nHeight, const CTransaction& tx, CValidationState& state)
{
    CAmount nBlockReward, nFounderPayment,
    veil::Budget().GetBlockRewards(nHeight, nBlockReward, nFounderPayment);
    std::string strFounderAddress = Budget().GetFounderAddress(); // KeyID for now
    CTxDestination destFounder = DecodeDestination(strFounderAddress);
    auto founderScript = GetScriptForDestination(destFounder);
    bool fFounderPayment = !nFounderPayment;
    for (auto pOut : tx.vpout) {
        if (pOut->nVersion != OUTPUT_STANDARD)
            continue;
        auto txOut = (CTxOutStandard*)pOut.get();
        if (txOut->scriptPubKey == founderScript) {
            if (txOut->nValue == nFounderPayment)
                fFounderPayment = true;
        }
    }
    if (!fFounderPayment)
        LogPrintf("%s: Expected founder payment not found in coinbase transaction\n", __func__);
    return fBudgetPayment && fLabPayment && fFounderPayment;
}
/**
 * Rewards are generated once a month. If not the right block height then the rewards are set to 0.
 * Rewards are based upon the height of the block.
 * @param nBlockHeight
 */
void BudgetParams::GetBlockRewards(int nBlockHeight, CAmount& nBlockReward,
        CAmount& nFounderPayment
{
    if (nBlockHeight <= 0 || nBlockHeight > Params().HeightSupplyCreationStop()) { // 43830 is the average size of a month in minutes when including leap years
        nBlockReward = 0;
        nFounderPayment = 0;
    } else if (nBlockHeight >= 1 && nBlockHeight <= 262980) {//6mo

        nBlockReward = 50;
            nFounderPayment = 50 * nBlocksPerPeriod;

    } else if (nBlockHeight >= 262981 && nBlockHeight <= 525960) {
        nBlockReward = 25;
            nFounderPayment = 10 * nBlocksPerPeriod;
    } else if (nBlockHeight >= 525961 && nBlockHeight <= 788940) {
        nBlockReward = 12.5;
            nFounderPayment = 3.75 * nBlocksPerPeriod;
    } else if (nBlockHeight >= 788941 && nBlockHeight <= 1051920) {
        nBlockReward = 6.25;
            nFounderPayment = 1.25 * nBlocksPerPeriod;
    } else if (nBlockHeight >= 1051921 && nBlockHeight <= 1314900) {
        nBlockReward = 3.125;
            nFounderPayment = 0.46875 * nBlocksPerPeriod;    
    } else {
        nBlockReward = 1;
            nFounderPayment = 0.1 * nBlocksPerPeriod;  
    }
    nBlockReward *= COIN;
    nFounderPayment *= COIN;
}

BudgetParams::BudgetParams(std::string strNetwork)
{
    // Addresses must decode to be different, otherwise CheckBudgetTransaction() will fail
    if (strNetwork == "main") {

        founderAddress = "";

    } else if (strNetwork == "test") {

        founderAddress = "";

    } else if (strNetwork == "regtest") {

        founderAddress = "";

    }
}

BudgetParams* BudgetParams::Get()
{
    std::string strNetwork = Params().NetworkIDString();
    static BudgetParams instance(strNetwork);
    return &instance;
}
BudgetParams& Budget()
{
    return *BudgetParams::Get();
}
}

