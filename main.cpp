#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){
    list<Transaction> firstList;
    list<Transaction> secondList;

    readJsonFile(firstList, "bank.json");
    readJsonFile(secondList, "gl.json");
    
    //Transactions matched to find duplicates
    list<list<Transaction> > matchedTransactions = matchTransactions(firstList, secondList);
    //Transactions matched to find probable duplicates
    list<list<Transaction> > probableMatchedTransactions = probableMatchTransactions(firstList, secondList);
    //Transactions that definitely have no matches
    list<Transaction> unmatchedTransactions = unmatchTransactions(firstList, secondList);

    //Converts to a json list of lists of Transactions
    json jsonMatchedTransactions = convertToJsonListOfLists(matchedTransactions, "matched_transactions", "percent_matching");
    json jsonProbableMatchedTransactions = convertToJsonListOfLists(probableMatchedTransactions, "probable_matches", "percent_matching");
    //Converts to a json list of Transactions
    json jsonUnmatchedTransactions = convertToJsonList(unmatchedTransactions, "unmatched_transactions");

    //Converts the three individual json objects to a final one
    json combinedJsonObject = makeJsonObject(jsonMatchedTransactions, jsonProbableMatchedTransactions, jsonUnmatchedTransactions);

    cout << "*************************************" << endl;
    cout << "TRANSACTIONS" << endl;
    cout << "*************************************" << endl;

    cout << "MATCHES = " << ends;
    display(matchedTransactions);
    cout << "*************************************" << endl;

    cout << "PROBABLE MATCHES = " << ends;
    display(probableMatchedTransactions);
    cout << "*************************************" << endl;

    cout << "UNMATCHED = " << ends;
    display(unmatchedTransactions);
    cout << "*************************************" << endl;
    cout << "*************************************" << endl;
    cout << "JSON REPRESENTATION" << endl;
    cout << combinedJsonObject.dump(4) << endl;

    return 0;
}