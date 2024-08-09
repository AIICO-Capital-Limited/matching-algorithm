#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "Transaction.h"
#include "Constants.h"

using namespace std;

int diffDates(string date1, string date2);
double withinDateRange(string date1, string date2);
double relatedNarration(string narration, string narration2);
bool isMatched(Transaction transaction1, Transaction transaction2, int percentToMatch);
list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction> secondList);
list<list<Transaction> > probableMatchTransactions(list<Transaction> firstList, list<Transaction> secondList);
list<Transaction> unmatchTransactions(list<Transaction> firstList, list<Transaction> secondList);
void display(list<list<Transaction> > matchedTransactions);
void display(list<Transaction> unmatchedTransactions);
list<string> splitString(string sentence, char separator);
double percentMatching(Transaction transaction1, Transaction transaction2);

#endif