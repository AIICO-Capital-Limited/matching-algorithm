#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){
    //All the transactions included initially in one array
    list<Transaction> sourceArray;
    sourceArray.push_back(Transaction(1, 50, "20/07/2024", "Transaction of 50 Niara to my account", 2));
    sourceArray.push_back(Transaction(1, 40, "29/07/2024", "Transaction to my mum", 1));
    sourceArray.push_back(Transaction(1, 40, "21/07/2024", "Transaction3", 2));
    sourceArray.push_back(Transaction(1, 40, "23/07/2024", "Transaction1", 1));
    sourceArray.push_back(Transaction(1, 50, "23/07/2024", "Transaction of 50 Naira to me", 1));
    
    //Transactions sorted into their appropriate arrays
    list<Transaction> array1;
    list<Transaction> array2;
    sortTransactions(array1, array2, sourceArray);

    //Transactions matched to find duplicates
    list<list<Transaction> > matchedTransactions = matchTransactions(array1, array2);
    display(matchedTransactions);
    return 0;
}