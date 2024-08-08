#include "Transaction.h"

Transaction::Transaction(int id, int value, string date, string narration, int arrayId){
    Transaction::id = id;
    Transaction::value = value;
    Transaction::date = date;
    Transaction::narration = narration;
    Transaction::arrayId = arrayId;
}

int Transaction::getId(){
    return Transaction::id;
}

int Transaction::getVal(){
    return Transaction::value;
}

string Transaction::getDate(){
    return Transaction::date;
}

string Transaction::getNarration(){
    return Transaction::narration;
}

int Transaction::getArrayId(){
    return Transaction::arrayId;
}