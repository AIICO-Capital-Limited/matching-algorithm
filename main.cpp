#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
    list<Transaction> firstList;
    list<Transaction> secondList;

    ifstream bankTransfersFile("bank.json");
    json dataFromJson;
    bankTransfersFile >> dataFromJson;
    for(const auto& data : dataFromJson["data"]){
        int id = data["id"];
        int value = data["value"];
        string date = data["date"];
        string narration = data["narration"];

        firstList.push_back(Transaction(id, value, date, narration));
    }

    ifstream glTransfersFile("gl.json");
    json dataFromJson2;
    glTransfersFile >> dataFromJson2;
    for(const auto& data : dataFromJson2["data"]){
        int id = data["id"];
        int value = data["value"];
        string date = data["date"];
        string narration = data["narration"];

        secondList.push_back(Transaction(id, value, date, narration));
    }

    
    //Transactions matched to find duplicates
    list<list<Transaction> > matchedTransactions = matchTransactions(firstList, secondList);
    //Transactions matched to find probable duplicates
    list<list<Transaction> > probableMatchedTransactions = probableMatchTransactions(firstList, secondList);
    //Transactions that definitely have no matches
    list<Transaction> unmatchedTransactions = unmatchTransactions(firstList, secondList);

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