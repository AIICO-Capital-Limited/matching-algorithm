#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){
    //All the transactions included initially in one array
    list<Transaction> sourceArray;
    sourceArray.push_back(Transaction(2, 50, "20/07/2024", "Transaction of 50 Niara to my account", 2));
    sourceArray.push_back(Transaction(1, 40, "29/07/2024", "Transaction to my mum", 1));
    sourceArray.push_back(Transaction(1, 40, "21/07/2024", "Transaction3", 2));
    sourceArray.push_back(Transaction(1, 40, "23/07/2024", "Transaction1", 1));
    sourceArray.push_back(Transaction(1, 50, "23/07/2024", "Transaction of 50 Naira to me", 1));
    sourceArray.push_back(Transaction(1, 5, "23/07/2024", "Transaction of 5 Naira to bro", 2));
    sourceArray.push_back(Transaction(3, 5, "23/07/2024", "Transaction of 5 Naira to bro", 1));
    sourceArray.push_back(Transaction(4, 70, "23/07/2024", "70 Naira", 1));
    sourceArray.push_back(Transaction(7, 70, "23/07/2024", "70 Naira", 2));
    
    //Transactions matched to find duplicates
    list<list<Transaction> > matchedTransactions = matchTransactions(sourceArray);
    //Transactions matched to find probable duplicates
    list<list<Transaction> > probableMatchedTransactions = probableMatchTransactions(sourceArray);
    //Transactions that definitely have no matches
    list<Transaction> unmatchedTransactions = unmatchTransactions(sourceArray);

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
    return 0;
}