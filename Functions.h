#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <list>
#include <string>
#include "Transaction.h"
#include "Constants.h"

using namespace std;

int diffDates(string date1, string date2);
bool withinDateRange(string date1, string date2);
bool relatedNarration(string narration, string narration2);
list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction> secondList);
void display(list<list<Transaction> > matchedTransactions);
void sortTransactions(list<Transaction>& destinationArray1, list<Transaction>& destinationArray2, list<Transaction> sourceArray);
list<string> splitString(string sentence, char separator);

#endif