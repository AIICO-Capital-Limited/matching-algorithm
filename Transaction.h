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

    public:
    Transaction(int id, int value, string date, string narration);
    int getId();
    int getVal();
    string getDate();
    string getNarration();
    void toString();
    json toJson() const;
};

#endif