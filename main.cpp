#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){

    cout << "*************************************" << endl;
    cout << "TRANSACTIONS" << endl;
    cout << "*************************************" << endl;

    getMatchedProbableMatchAndUnmatched("bank.json", "gl.json", "output.json", "matched_transaction", "probabe_matches", "unmatched_transactions", "percent_matching");

    return 0;
}