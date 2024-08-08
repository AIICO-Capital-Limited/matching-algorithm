#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Transaction {
    private:
    int id;
    int value;
    string date;
    string narration;
    int arrayId;

    public:
    Transaction(int id, int value, string date, string narration, int arrayId);
    int getId();
    int getVal();
    string getDate();
    string getNarration();
    int getArrayId();
};

#endif