#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){

    getMatchedProbableMatchAndUnmatched("bank.json", "gl.json", "output.json", "matched_transaction", "probable_matches", "unmatched_transactions", "percent_matching");

    // list<Transaction> firstList;
    // list<Transaction> secondList;

    // readJsonFile(firstList, "bank.json");
    // readJsonFile(secondList, "gl.json");

    // list<list<Transaction>> matchedTransactions = matchTransactions(firstList, secondList);
    // list<list<Transaction>> probableMatchedTransactions = probableMatchTransactions(firstList, secondList);
    // list<Transaction> unmatchedTransactions = unmatchTransactions(firstList, secondList);

    // cout << "Matched Transactions: " << endl;
    // display(matchedTransactions);
    // cout << "Probable Matched Transactions: " << endl;
    // display(probableMatchedTransactions);
    return 0;
}