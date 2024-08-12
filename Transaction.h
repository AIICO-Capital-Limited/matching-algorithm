#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <ctime>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Transaction {
    private:
    int id;
    int value;
    string date;
    string narration;
    string tableId;

    public:
    Transaction(int id, int value, string date, string narration, string tableId);
    int getId();
    int getVal();
    string getDate();
    string getNarration();
    string getTableId();
    void toString();
    json toJson() const;
};

#endif