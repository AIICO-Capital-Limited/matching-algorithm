#include "Transaction.h"

Transaction::Transaction(int id, int value, string date, string narration, string tableId){
    Transaction::id = id;
    Transaction::value = value;
    Transaction::date = date;
    Transaction::narration = narration;
    Transaction::tableId = tableId;
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

string Transaction::getTableId(){
    return Transaction::tableId;
}
void Transaction::toString(){
    cout << "{" << ends;
    cout << "id:  " << Transaction::id << ", "<< ends;
    cout << "value: " << Transaction::value << ", " << ends;
    cout << "date: " << Transaction::date << ", " << ends;
    cout << "narration: " << Transaction::narration << ", " << ends;
    cout << "table ID: " << Transaction::tableId << endl;
    cout << "}" << ends;
}

json Transaction::toJson() const{
    return json{{"id", Transaction::id}, {"value", Transaction::value}, {"date", Transaction::date}, {"narration", Transaction::narration}, {"table_ID", Transaction::tableId}};
}