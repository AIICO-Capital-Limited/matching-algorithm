#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){

    // getMatchedProbableMatchAndUnmatched("bank.json", "gl.json", "output.json", "matched_transaction", "probable_matches", "unmatched_transactions", "percent_matching");
    repairList(581, "GL", "unmatched_transactions", 249, "GL", "matched_transaction", "output.json");
    
    return 0;
}