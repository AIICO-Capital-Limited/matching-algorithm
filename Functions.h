#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <stdexcept>
#include "Transaction.h"
#include "Constants.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


int diffDates(string date1, string date2);
double withinDateRange(string date1, string date2);
double relatedNarration(string narration, string narration2);
double averagePercentMatching(list<Transaction> matchingTransactions);
bool isMatched(Transaction transaction1, Transaction transaction2, int percentToMatch);
list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction>& secondList);
list<list<Transaction> > probableMatchTransactions(list<Transaction> firstList, list<Transaction> secondList);
list<Transaction> unmatchTransactions(list<Transaction> firstList, list<Transaction> secondList);
void filterToUnmatched(list<list<Transaction>>& matchingTransactions, list<Transaction>& unmatchedTransactions, list<list<Transaction>>& otherList);
void filterMultipleToUnmatched(list<list<Transaction>>& matchingTransactions, list<Transaction>& unmatchTransactions, list<list<Transaction>> otherList);
void display(list<list<Transaction> > matchedTransactions);
void display(list<Transaction> unmatchedTransactions);
int countLeapYearDays(int d[]);
list<string> splitString(string sentence, char separator);
double percentMatching(Transaction transaction1, Transaction transaction2);
void readJsonFile(list<Transaction>& listOfTransaction, string nameOfFile);
void readJsonArray(list<Transaction>& listOfTransactions, const json& jsonArray);
json convertToJsonListOfLists(list<list<Transaction> > Transactions, string name, string nameForPercentMatching);
json convertToJsonList(list<Transaction> Transaction, string name);
json makeJsonObject(json firstList, json secondList, json thirdList);
json getMatchedProbableMatchAndUnmatched(string fileToReadFrom, string secondFileToReadFrom, string fileToOutputTo, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions);
json getMatchedProbableMatchAndUnmatchedFromJsonLists(json firstJsonToReadFrom, json secondJsonToReadFrom, string fileToOutputTo, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions);
json repairList(int idTaken, string tableIdTaken, string listTakenFrom, int idTo, string tableIdTo, string listTakenTo, string inputFile);
json repairListJson(int idTaken, string tableIdTaken, string listTakenFrom, int idTo, string tableIdTo, string listTakenTo, json inputFile);
json manuallyMatch(int id1, string tableId1, string list1, int id2, string tableId2, string list2, string input);
json manuallyMatchJson(int id1, string tableId1, string list1, int id2, string tableId2, string list2, json input);
void readForAdjustments(list<list<Transaction>>& listOfTransactions, string inputFile, string nameOfTable);
void readForAdjustments(list<Transaction>& listOfTransactions, string nameOfTable, string inputFile);
void readForAdjustmentsJson(list<list<Transaction>>& listOfTransactions, json jsonObject, string nameOfTable);
void readForAdjustmentsJson(list<Transaction>& listOfTransactions, string nameOfTable, json jsonObject);
string determineNameOfTheLastList(string listTakenFrom, string listTakenTo, string inputFile);
string determineNameOfTheLastListJson(string listTakenFrom, string listTakenTo, json inputFile);
void takeOutTransaction(list<list<Transaction>>& listRemovingFrom, list<Transaction>& listAddedto, int idTaken, string tableIdTaken);
void takeOutTransaction(list<Transaction>& listRemovingFrom, list<Transaction>& listAddedto, int idTaken, string tableIdTaken);
void reorderListofManuallyMatchedTransactions(list<Transaction>& matchedTrans, list<list<Transaction>> listOfLists);
void displayJsonInFile(json jsonObject, string nameOfFile);
void addRelevantTransaction(list<list<Transaction>>& listToAddTo, list<Transaction>& listToRemoveFrom, int idTo, string tableIdTo);


#endif