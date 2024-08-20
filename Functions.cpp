#include "Functions.h"

list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction>& secondList){
    list<list<Transaction> > matchingTrans;
    list<Transaction> transactionsThatHaveMatches;
    list<Transaction> transactionsThatMatched;
    for(auto Itr = begin(firstList); Itr != end(firstList); Itr++){
        for(auto Itr2 = begin(secondList); Itr2 != end(secondList); Itr2++){
            if(isMatched(*Itr, *Itr2, PERCENT_TO_MATCH)){
                transactionsThatHaveMatches.push_back(*Itr);
                break;
            }
        }
    }

    for(auto itr = begin(transactionsThatHaveMatches); itr != end(transactionsThatHaveMatches); itr++){
        list<Transaction> subMatches;
        subMatches.push_back(*itr);
        for(auto itr2 = begin(secondList); itr2 != end(secondList); itr2++){
            bool alreadyMatched = false;
            for(auto itr3 = begin(transactionsThatMatched); itr3 != end(transactionsThatMatched); itr3++){
                if(isMatched(*itr2, *itr3, 100)){
                    alreadyMatched = true;
                    break;
                }
            }

            if(!alreadyMatched && isMatched(*itr, *itr2, PERCENT_TO_MATCH)){
                subMatches.push_back(*itr2);
                transactionsThatMatched.push_back(*itr2);
                itr2 = secondList.erase(itr2);
            }
        }
        matchingTrans.push_back(subMatches);
    }

    for(auto itr = begin(matchingTrans); itr != end(matchingTrans); itr++){
        for(auto itr2 = begin(matchingTrans); itr2 != end(matchingTrans); itr2++){
            for(auto itr3 = begin(*itr2); itr3 != end(*itr2); itr3++){
                if(itr3 != begin(*itr2)){
                    if(percentMatching(itr->front(), *itr3) > percentMatching(itr2->front(), *itr3)){
                        itr->push_back(*itr3);
                        itr3 = itr2->erase(itr3);
                    }
                }
            }
        }
    }

    return matchingTrans;
}

list<list<Transaction> > probableMatchTransactions(list<Transaction> firstList, list<Transaction> secondList){
    list<list<Transaction> > probableMatchTrans;
    list<Transaction> transactionsThatHaveMatches;
    list<Transaction> transactionsThatMatched;
    for(auto Itr = begin(firstList); Itr != end(firstList); Itr++){
        for(auto Itr2 = begin(secondList); Itr2 != end(secondList); Itr2++){
            if(isMatched(*Itr, *Itr2, PERCENT_TO_PROB_MATCH) && !isMatched(*Itr, *Itr2, PERCENT_TO_MATCH)){
                transactionsThatHaveMatches.push_back(*Itr);
                break;
            }
        }
    }

    for(auto itr = begin(transactionsThatHaveMatches); itr != end(transactionsThatHaveMatches); itr++){
        list<Transaction> subProbMatches;
        subProbMatches.push_back(*itr);
        for(auto itr2 = begin(secondList); itr2 != end(secondList); itr2++){
            bool alreadyMatched = false;
            for(auto itr3 = begin(transactionsThatMatched); itr3 != end(transactionsThatMatched); itr3++){
                if(isMatched(*itr2, *itr3, 100)){
                    alreadyMatched = true;
                    break;
                }
            }

            if(!alreadyMatched && isMatched(*itr, *itr2, PERCENT_TO_PROB_MATCH) && !isMatched(*itr, *itr2, PERCENT_TO_MATCH)){
                subProbMatches.push_back(*itr2);
                transactionsThatMatched.push_back(*itr2);
            }
        }

        probableMatchTrans.push_back(subProbMatches);
    }

    for(auto itr = begin(probableMatchTrans); itr != end(probableMatchTrans); itr++){
        for(auto itr2 = begin(probableMatchTrans); itr2 != end(probableMatchTrans); itr2++){
            for(auto itr3 = begin(*itr2); itr3 != end(*itr2); itr3++){
                if(itr3 != begin(*itr2)){
                    if(percentMatching(itr->front(), *itr3) > percentMatching(itr2->front(), *itr3)){
                        itr->push_back(*itr3);
                        itr3 = itr2->erase(itr3);
                    }
                }
            }
        }
    }

    return probableMatchTrans;
}

list<Transaction> unmatchTransactions(list<Transaction> firstList, list<Transaction> secondList){
    list<Transaction> unmatchedTrans;
    for(auto Itr = begin(firstList); Itr != end(firstList); Itr++){
        bool isMatching = false;
        for(auto Itr2 = begin(secondList); Itr2 != end(secondList); Itr2++){
            if(isMatched(*Itr, *Itr2, PERCENT_TO_PROB_MATCH) || isMatched(*Itr, *Itr2, PERCENT_TO_MATCH)){
                isMatching = true;
            }
        }
        if(!isMatching){
            unmatchedTrans.push_back(*Itr);
        }
    }

    for(auto Itr = begin(secondList); Itr != end(secondList); Itr++){
        bool isMatching = false;
        for(auto Itr2 = begin(firstList); Itr2 != end(firstList); Itr2++){
            if(isMatched(*Itr, *Itr2, PERCENT_TO_PROB_MATCH) || isMatched(*Itr, *Itr2, PERCENT_TO_MATCH)){
                isMatching = true;
            }
        }
        if(!isMatching){
            unmatchedTrans.push_back(*Itr);
        }
    }

    return unmatchedTrans;
}

int diffDates(string date1, string date2){
    const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

    int yearOfDate1 = stoi(date1.substr(6, 4));
    int monthOfDate1 = stoi(date1.substr(3, 2));
    int dayOfDate1 = stoi(date1.substr(0, 2));
    int yearOfDate2 = stoi(date2.substr(6, 4));
    int monthOfDate2 = stoi(date2.substr(3, 2));
    int dayOfDate2 = stoi(date2.substr(0, 2));

    int date1Array[] = {dayOfDate1, monthOfDate1, yearOfDate1};
    int date2Array[] = {dayOfDate2, monthOfDate2, yearOfDate2};

    long int dayCount1 = (date1Array[2] * 365);
    dayCount1 += monthDays[date1Array[1]];
    dayCount1 += date1Array[0];
    dayCount1 += countLeapYearDays(date1Array);
    long int dayCount2 = (date2Array[2] * 365);
    dayCount2 += monthDays[date2Array[1]];
    dayCount2 += date2Array[0];
    dayCount2 += countLeapYearDays(date2Array);
    return ( abs(dayCount1 - dayCount2) );
}

double withinDateRange(string date1, string date2){
    double percentOfDateMatch = 100.0 - (static_cast<double>(diffDates(date1, date2)) * (100.0/static_cast<double>(DAYS_TO_MATCH)));
    if(percentOfDateMatch >= 0){
        return percentOfDateMatch;
    }else{
        return 0.0;
    }
}

double relatedNarration(string narration1, string narration2){
    transform(narration1.begin(), narration1.end(), narration1.begin(), ::tolower);
    transform(narration2.begin(), narration2.end(), narration2.begin(), ::tolower);

    double percentOfMatches = 0.0;
    list<string> firstSeparation = splitString(narration1, ' ');
    int lengthOfFirstNarration = firstSeparation.size();
    list<string> secondSeparation = splitString(narration2, ' ');
    int lengthOfSecondNarration = secondSeparation.size();

    if(lengthOfFirstNarration >= lengthOfSecondNarration){
        int numberOfMatches = 0;
        for(auto itr = begin(firstSeparation); itr != end(firstSeparation); itr++){
            for(auto itr2 = begin(secondSeparation); itr2 != end(secondSeparation); itr2++){
                if((*itr).compare(*itr2) == 0){
                    numberOfMatches++;
                    break;
                }
            }
        }

        percentOfMatches = static_cast<double>(numberOfMatches)/static_cast<double>(lengthOfFirstNarration) * 100.0;
    }else{
        int numberOfMatches = 0;
        for(auto itr = begin(secondSeparation); itr != end(secondSeparation); itr++){
            for(auto itr2 = begin(firstSeparation); itr2 != end(firstSeparation); itr2++){
                if((*itr).compare(*itr2) == 0){
                    numberOfMatches++;
                    break;
                }
            }
        }

        percentOfMatches = static_cast<double>(numberOfMatches)/static_cast<double>(lengthOfSecondNarration) * 100.0;
    }

    return percentOfMatches;
}

void display(list<list<Transaction> > matchedTransactions){
    cout << "[" << ends;
    for(auto itr = begin(matchedTransactions); itr != end(matchedTransactions); itr++){
        cout << "[" << ends;
        for(auto itr2 = begin(*itr); itr2 != end(*itr); itr2++){
            auto itr3 = itr2;
            auto itr5 = itr2;
            if((++itr3) == end(*itr)){
                itr2->toString();
                cout << ", " << percentMatching(*itr2, *(--itr5));
            }else{
                itr2->toString();
                cout << ", " << endl;
            }
        }
        auto itr4 = itr;
        if((++itr4) == end(matchedTransactions)){
            cout << "]" << ends;
        }else{
            cout << "]," << endl;
        }
    }
    cout << "]" << endl;
}

void display(list<Transaction> unmatchedTransactions){
    cout << "[" << ends;
    for(auto itr = begin(unmatchedTransactions); itr != end(unmatchedTransactions); itr++){
        auto itr2 = itr;
        if((++itr2) == end(unmatchedTransactions)){
            itr->toString();
        }else{
            itr->toString();
            cout << ", " << endl;
        }
    }
    cout << "]" << endl;
}

list<string> splitString(string sentence, char seperator){
    transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);
    string result = "";
    for (char c : sentence) {
        if (!ispunct(c)) {
            result += c;
        }
    }
    sentence = result;

    int i = 0;  
    int startIndex = 0;
    int endIndex = 0;
    list<string> splitStr;
    bool containsSep = false;
    if(sentence.find(seperator) != string::npos){
        containsSep = true;
    }

    if(containsSep){
        while (i <= sentence.length())  
        {  
            if (sentence[i] == seperator || i == sentence.length())  
            {  
                endIndex = i;  
                string subStr = "";  
                subStr.append(sentence, startIndex, endIndex - startIndex);  
                splitStr.push_back(subStr);    
                startIndex = endIndex + 1;  
            }  
            i++;  
        }
    }else{
        splitStr.push_back(sentence);
    }
    return splitStr;
}

bool isMatched(Transaction transaction1, Transaction transaction2, int percentToMatch){
    return (percentMatching(transaction1, transaction2) >= percentToMatch);
}

double percentMatching(Transaction transaction1, Transaction transaction2){
    double percentOfValMatch;
    double percentOfDateMatch;
    double percentOfNarrMatch;
    double matchPercent;
    
    if(transaction1.getVal() == transaction2.getVal()){
        percentOfValMatch = 100.0;
    }

    percentOfDateMatch = withinDateRange(transaction1.getDate(), transaction2.getDate());

    percentOfNarrMatch = relatedNarration(transaction1.getNarration(), transaction2.getNarration());

    matchPercent = (percentOfValMatch + percentOfDateMatch + percentOfNarrMatch) / 3.0;

    return matchPercent;
}

double averagePercentMatching(list<Transaction> matchingTransactions){
    double lengthOfMatchingTrans = matchingTransactions.size();
    double totalMatchPercentage = 0;

    if(matchingTransactions.size() > 1){
        for(auto itr = begin(matchingTransactions); itr != end(matchingTransactions); itr++){
            if(itr != begin(matchingTransactions)){
                totalMatchPercentage += percentMatching(matchingTransactions.front(), *itr);
            }
        }

        return (totalMatchPercentage / (lengthOfMatchingTrans - 1.0));
    }else{
        return 100.0;
    }
}

void filterToUnmatched(list<list<Transaction>>& matchingTransactions, list<Transaction>& unmatchedTransactions, list<list<Transaction>>& otherList){
    for(auto itr = begin(matchingTransactions); itr != end(matchingTransactions); itr++){
        bool exists = false;
        if(itr->size() == 1){
            for(auto itr2 = begin(otherList); itr2 != end(otherList); itr2++){
                for(auto itr3 = begin(*itr2); itr3 != end(*itr2); itr3++){
                    if(isMatched(itr->front(), *itr3, 100)){
                        exists = true;
                    }
                }
            }

            if(exists){
                itr = matchingTransactions.erase(itr);
                --itr; 
            }else{
                unmatchedTransactions.push_back(itr->front());
                itr = matchingTransactions.erase(itr);
                --itr;
            }
        }
    }
}

void readJsonFile(list<Transaction>& listOfTransaction, string nameOfFile){
    ifstream jsonFile(nameOfFile);
    json dataFromJson;
    jsonFile >> dataFromJson;
    for(const auto& data : dataFromJson["data"]){
        int id = data["id"];
        double value = data["value"];
        string date = data["date"];
        string narration = data["narration"];
        string tableId = dataFromJson["type"];

        listOfTransaction.push_back(Transaction(id, value, date, narration, tableId));
    }
}

void readJsonArray(list<Transaction>& listOfTransactions, const json& jsonArray){
    for(const auto& data : jsonArray["data"]){
        int id = data["id"];
        double value = data["value"];
        string date = data["date"];
        string narration = data["narration"];
        string tableId = jsonArray["type"];

        listOfTransactions.push_back(Transaction(id, value, date, narration, tableId));
    }
}

json convertToJsonListOfLists(list<list<Transaction> > Transactions, string name, string nameForPercentMatching){
    json matchedTransaction = json::array();

    for(auto itr = begin(Transactions); itr != end(Transactions); itr++){
        json subMatchedTransaction = json::array();
        for(auto itr2 = begin(*itr); itr2 != end(*itr); itr2++){
            auto itr3 = itr2;
            auto itr4 = itr2;
            if((++itr3) == end(*itr)){
                subMatchedTransaction.push_back(itr2->toJson());
                subMatchedTransaction.push_back(json{{nameForPercentMatching, averagePercentMatching(*itr)}});
            }else{
                subMatchedTransaction.push_back(itr2->toJson());
            }
        }
        matchedTransaction.push_back(subMatchedTransaction);
    }

    json namedMatchedTransaction = json{name, matchedTransaction};
    return namedMatchedTransaction;
}

json convertToJsonList(list<Transaction> Transaction, string name){
    json unmatchedTransactions = json::array();

    for(const auto& transaction : Transaction){
        unmatchedTransactions.push_back(transaction.toJson());
    }

    json namedUnmatchedTransactions = json{name, unmatchedTransactions};

    return namedUnmatchedTransactions;
}

json makeJsonObject(json firstList, json secondList, json thirdList){
    return json{firstList, secondList, thirdList};
}

int countLeapYearDays(int d[]){
   int years = d[2];
   if (d[1] <= 2)
      years--;
   return ( (years / 4) - (years / 100) + (years / 400) );
}

json getMatchedProbableMatchAndUnmatched(string firstFileToReadFrom, string secondFileToReadFrom, string fileToOutputTo, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions){
    list<Transaction> firstList;
    list<Transaction> secondList;
    string nameForPercentageMatched = "percent_matching";

    readJsonFile(firstList, firstFileToReadFrom);
    readJsonFile(secondList, secondFileToReadFrom);

    list<list<Transaction>> matchedTransactions = matchTransactions(firstList, secondList);
    list<list<Transaction>> probableMatchedTransactions = probableMatchTransactions(firstList, secondList);
    list<Transaction> unmatchedTransactions = unmatchTransactions(firstList, secondList);

    filterToUnmatched(matchedTransactions, unmatchedTransactions, probableMatchedTransactions);
    filterToUnmatched(probableMatchedTransactions, unmatchedTransactions, matchedTransactions);

    json jsonMatchedTransactions = convertToJsonListOfLists(matchedTransactions, nameForMatchedTransactions, nameForPercentageMatched);
    json jsonProbableMatchedTransactions = convertToJsonListOfLists(probableMatchedTransactions, nameForProbableMacthedTransactions, nameForPercentageMatched);
    json jsonUnmatchedTransactions = convertToJsonList(unmatchedTransactions, nameForUnmatchedTransactions);

    json combinedJsonObject = makeJsonObject(jsonMatchedTransactions, jsonProbableMatchedTransactions, jsonUnmatchedTransactions);

    displayJsonInFile(combinedJsonObject, fileToOutputTo);
    return combinedJsonObject;
}

json getMatchedProbableMatchAndUnmatchedFromJsonLists(json firstJsonToReadFrom, json secondJsonToReadFrom, string fileToOutputTo, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions){
    list<Transaction> firstList;
    list<Transaction> secondList;
    string nameForPercentageMatched = "percent_matching";

    readJsonArray(firstList, firstJsonToReadFrom);
    readJsonArray(secondList, secondJsonToReadFrom);

    list<list<Transaction>> matchedTransactions = matchTransactions(firstList, secondList);
    list<list<Transaction>> probableMatchedTransactions = probableMatchTransactions(firstList, secondList);
    list<Transaction> unmatchedTransactions = unmatchTransactions(firstList, secondList);

    filterToUnmatched(matchedTransactions, unmatchedTransactions, probableMatchedTransactions);
    filterToUnmatched(probableMatchedTransactions, unmatchedTransactions, matchedTransactions);

    json jsonMatchedTransactions = convertToJsonListOfLists(matchedTransactions, nameForMatchedTransactions, nameForPercentageMatched);
    json jsonProbableMatchedTransactions = convertToJsonListOfLists(probableMatchedTransactions, nameForProbableMacthedTransactions, nameForPercentageMatched);
    json jsonUnmatchedTransactions = convertToJsonList(unmatchedTransactions, nameForUnmatchedTransactions);

    json combinedJsonObject = makeJsonObject(jsonMatchedTransactions, jsonProbableMatchedTransactions, jsonUnmatchedTransactions);

    displayJsonInFile(combinedJsonObject, fileToOutputTo);
    return combinedJsonObject;
}

void readForAdjustments(list<list<Transaction>>& listOfTransactions, string inputFile, string nameOfTable){
    ifstream jsonFile(inputFile);
    json dataFromJson;
    jsonFile >> dataFromJson;

    for(const auto& data : dataFromJson[nameOfTable]){
        int count = 0;
        list<Transaction> matchingTransactionGroups;
        for(const auto& data2 : data){
            count += 1;
            if(count < data.size()){
                string date = data2["date"];
                int id = data2["id"];
                string narration = data2["narration"];
                string tableId = data2["table_ID"];
                double value = data2["value"];

                matchingTransactionGroups.push_back(Transaction(id, value, date, narration, tableId));
            }
        }
        listOfTransactions.push_back(matchingTransactionGroups);
    }
}

void readForAdjustments(list<Transaction>& listOfTransactions, string nameOfTable, string inputFile){
    ifstream jsonFile(inputFile);
    json dataFromJson;
    jsonFile >> dataFromJson;

    for(const auto& data : dataFromJson[nameOfTable]){
        string date = data["date"];
        int id = data["id"];
        string narration = data["narration"];
        string tableId = data["table_ID"];
        double value = data["value"];

        listOfTransactions.push_back(Transaction(id, value, date, narration, tableId));
    }
}

void readForAdjustmentsJson(list<list<Transaction>>& listOfTransactions, json jsonObject, string nameOfTable){
    for(const auto& data : jsonObject[nameOfTable]){
        int count = 0;
        list<Transaction> matchingTransactionGroups;
        for(const auto& data2 : data){
            count += 1;
            if(count < data.size()){
                string date = data2["date"];
                int id = data2["id"];
                string narration = data2["narration"];
                string tableId = data2["table_ID"];
                double value = data2["value"];

                matchingTransactionGroups.push_back(Transaction(id, value, date, narration, tableId));
            }
        }
        listOfTransactions.push_back(matchingTransactionGroups);
    }
}

void readForAdjustmentsJson(list<Transaction>& listOfTransactions, string nameOfTable, json jsonObject){
    for(const auto& data : jsonObject[nameOfTable]){
        string date = data["date"];
        int id = data["id"];
        string narration = data["narration"];
        string tableId = data["table_ID"];
        double value = data["value"];

        listOfTransactions.push_back(Transaction(id, value, date, narration, tableId));
    }
}

string determineNameOfTheLastList(string listTakenFrom, string listTakenTo, string inputFile){
    string lastList;
    
    ifstream jsonFile(inputFile);
    json dataFromJson;
    jsonFile >> dataFromJson;

    for(auto itr = dataFromJson.begin(); itr != dataFromJson.end(); itr++){
        if((itr.key().compare(listTakenFrom) != 0) && (itr.key().compare(listTakenTo) != 0)){
            lastList = itr.key();
            break;
        }
    }

    return lastList;
}

string determineNameOfTheLastListJson(string listTakenFrom, string listTakenTo, json inputFile){
    string lastList;

    for(auto itr = inputFile.begin(); itr != inputFile.end(); itr++){
        if((itr.key().compare(listTakenFrom) != 0) && (itr.key().compare(listTakenTo) != 0)){
            lastList = itr.key();
            break;
        }
    }

    return lastList;
}

void takeOutTransaction(list<list<Transaction>>& listRemovingFrom, list<Transaction>& listAddedto, int idTaken, string tableIdTaken){
    for(auto itr = begin(listRemovingFrom); itr != end(listRemovingFrom); itr++){
        for(auto itr2 = begin(*itr); itr2 != end(*itr); itr2++){
            if(itr2->getId() == idTaken && (itr2->getTableId().compare(tableIdTaken) == 0)){
                listAddedto.push_back(*itr2);
                itr2 = itr->erase(itr2);
                break;
            }
        }
    }
}

void takeOutTransaction(list<Transaction>& listRemovingFrom, list<Transaction>& listAddedto, int idTaken, string tableIdTaken){
    for(auto itr = begin(listRemovingFrom); itr != end(listRemovingFrom); itr++){
        if(itr->getId() == idTaken && (itr->getTableId().compare(tableIdTaken) == 0)){
            listAddedto.push_back(*itr);
            itr = listRemovingFrom.erase(itr);
            break;
        }
    }
}

void addRelevantTransaction(list<list<Transaction>>& listToAddTo, list<Transaction>& listToRemoveFrom, int idTo, string tableIdTo){
    for(auto itr = begin(listToAddTo); itr != end(listToAddTo); itr++){
        for(auto itr2 = begin(*itr); itr2 != end(*itr); itr2++){
            if(itr2->getId() == idTo && (itr2->getTableId().compare(tableIdTo) == 0)){
                itr->push_back(listToRemoveFrom.front());
            }
        }
    }
}

void displayJsonInFile(json jsonObject, string nameOfFile){
    ofstream outputFile(nameOfFile);
    outputFile << jsonObject.dump(4);
    outputFile.close();
}

json repairList(int idTaken, string tableIdTaken, string listTakenFrom, int idTo, string tableIdTo, string listTakenTo, string inputFile){
    string standardizedListTakenFrom = listTakenFrom;
    string standardizedListTakenTo = listTakenTo;
    string nameForPercentMatching = "percent_matching";
    string nameOfOutputFile = "ChangedOutput.json";

    transform(standardizedListTakenFrom.begin(), standardizedListTakenFrom.end(), standardizedListTakenFrom.begin(), ::toupper);
    transform(standardizedListTakenTo.begin(), standardizedListTakenTo.end(), standardizedListTakenTo.begin(), ::toupper);

    if(standardizedListTakenFrom.find("UNMATCHED") == string::npos && standardizedListTakenTo.find("UNMATCHED") == string::npos){
        list<Transaction> transactionToBeChanged;
        list<list<Transaction>> matchingTrans;

        if(listTakenFrom.compare(listTakenTo) != 0){
            readForAdjustments(matchingTrans, inputFile, listTakenFrom);

            takeOutTransaction(matchingTrans, transactionToBeChanged, idTaken, tableIdTaken);

            list<list<Transaction>> listToTakeTo;

            readForAdjustments(listToTakeTo, inputFile, listTakenTo);

            addRelevantTransaction(listToTakeTo, transactionToBeChanged, idTo, tableIdTo);

            list<Transaction> unchangedList;
            string lastList = determineNameOfTheLastList(listTakenFrom, listTakenTo, inputFile);

            readForAdjustments(unchangedList, lastList, inputFile);

            filterToUnmatched(matchingTrans, unchangedList, listToTakeTo);

            json newTransactionList1 = convertToJsonListOfLists(matchingTrans, listTakenFrom, nameForPercentMatching);
            json newTransactionList2 = convertToJsonListOfLists(listToTakeTo, listTakenTo, nameForPercentMatching);
            json unchangedTransactionList = convertToJsonList(unchangedList, lastList);

            if((standardizedListTakenFrom.find("MATCHED") != string::npos) && (standardizedListTakenFrom.find("UNMATCHED") == string::npos) && (standardizedListTakenFrom.find("PROBABLE") == string::npos)){
                json fullJsonObject = makeJsonObject(newTransactionList1, newTransactionList2, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }else{
                json fullJsonObject = makeJsonObject(newTransactionList2, newTransactionList1, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }
        }else{
            readForAdjustments(matchingTrans, inputFile, listTakenFrom);

            takeOutTransaction(matchingTrans, transactionToBeChanged, idTaken, tableIdTaken);

            addRelevantTransaction(matchingTrans, transactionToBeChanged, idTo, tableIdTo);
            list<list<Transaction>> unchangedList1;
            string lastList1 = determineNameOfTheLastList(listTakenFrom, listTakenTo, inputFile);

            readForAdjustments(unchangedList1, inputFile, lastList1);

            list<Transaction> unchangedList2;
            string lastList2 = determineNameOfTheLastList(listTakenFrom, lastList1, inputFile);

            readForAdjustments(unchangedList2, lastList2, inputFile);

            filterToUnmatched(matchingTrans, unchangedList2, unchangedList1);

            json newTransactionList1 = convertToJsonListOfLists(matchingTrans, listTakenFrom, nameForPercentMatching);
            json unchangedTransactionList2 = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
            json unchangedTransactionList = convertToJsonList(unchangedList2, lastList2);

            if((standardizedListTakenFrom.find("MATCHED") != string::npos) && (standardizedListTakenFrom.find("UNMATCHED") == string::npos) && (standardizedListTakenFrom.find("PROBABLE") == string::npos)){
                json fullJsonObject = makeJsonObject(newTransactionList1, unchangedTransactionList2, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }else{
                json fullJsonObject = makeJsonObject(unchangedTransactionList2, newTransactionList1, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }
        }
    }else if(standardizedListTakenFrom.find("UNMATCHED") != string::npos && standardizedListTakenTo.find("UNMATCHED") == string::npos){
        list<Transaction> transactionsTobeChanged;
        list<Transaction> unmatchedTrans;

        readForAdjustments(unmatchedTrans, listTakenFrom, inputFile);

        takeOutTransaction(unmatchedTrans, transactionsTobeChanged, idTaken, tableIdTaken);

        list<list<Transaction>> receivingListOfTransactions;

        readForAdjustments(receivingListOfTransactions, inputFile, listTakenTo);

        addRelevantTransaction(receivingListOfTransactions, transactionsTobeChanged, idTo, tableIdTo);

        list<list<Transaction>> unchangedList;
        string lastList = determineNameOfTheLastList(listTakenFrom, listTakenTo, inputFile);

        readForAdjustments(unchangedList, inputFile, lastList);

        json newTransactionList1 = convertToJsonListOfLists(receivingListOfTransactions, listTakenTo, nameForPercentMatching);
        json unchangedTransactionList = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
        json newTransactionList2 = convertToJsonList(unmatchedTrans, listTakenFrom);

        if((standardizedListTakenTo.find("MATCHED") != string::npos) && (standardizedListTakenTo.find("UNMATCHED") == string::npos) && (standardizedListTakenTo.find("PROBABLE") == string::npos)){
            json fullJsonObject = makeJsonObject(newTransactionList1, unchangedTransactionList, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }else{
            json fullJsonObject = makeJsonObject(unchangedTransactionList, newTransactionList1, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }
    }else if(standardizedListTakenFrom.find("UNMATCHED") == string::npos && standardizedListTakenTo.find("UNMATCHED") != string::npos){
        list<Transaction> transactionToBeChanged;
        list<list<Transaction>> matchingTrans;

        readForAdjustments(matchingTrans, inputFile, listTakenFrom);

        takeOutTransaction(matchingTrans, transactionToBeChanged, idTaken, tableIdTaken);

        list<Transaction> listToTakeTo;

        readForAdjustments(listToTakeTo, listTakenTo, inputFile);

        listToTakeTo.push_back(transactionToBeChanged.front());

        list<list<Transaction>> unchangedList;
        string lastList = determineNameOfTheLastList(listTakenFrom, listTakenTo, inputFile);

        readForAdjustments(unchangedList, inputFile, lastList);

        filterToUnmatched(matchingTrans, listToTakeTo, unchangedList);

        json newTransactionList1 = convertToJsonListOfLists(matchingTrans, listTakenFrom, nameForPercentMatching);
        json unchangedTransactionList = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
        json newTransactionList2 = convertToJsonList(listToTakeTo, listTakenTo);

        if((standardizedListTakenFrom.find("MATCHED") != string::npos) && (standardizedListTakenFrom.find("UNMATCHED") == string::npos) && (standardizedListTakenFrom.find("PROBABLE") == string::npos)){
            json fullJsonObject = makeJsonObject(newTransactionList1, unchangedTransactionList, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }else{
            json fullJsonObject = makeJsonObject(unchangedTransactionList, newTransactionList1, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }
    }else if(standardizedListTakenFrom.find("UNMATCHED") != string::npos && standardizedListTakenTo.find("UNMATCHED") != string::npos){
        list<Transaction> transactionsToBeChanged;
        list<Transaction> unmatchedTrans;

        readForAdjustments(unmatchedTrans, listTakenFrom, inputFile);

        list<list<Transaction>> unchangedList1;
        string lastList1 = determineNameOfTheLastList(listTakenFrom, listTakenTo, inputFile);
        string standardizedLastList1 = lastList1;
        transform(standardizedLastList1.begin(), standardizedLastList1.end(), standardizedLastList1.begin(), ::toupper);

        readForAdjustments(unchangedList1, inputFile, lastList1);

        list<list<Transaction>> unchangedList2;
        string lastList2 = determineNameOfTheLastList(listTakenFrom, lastList1, inputFile);

        readForAdjustments(unchangedList2, inputFile, lastList2);

        json newTransactionList1 = convertToJsonList(unmatchedTrans, listTakenFrom);
        json unchangedTransactionList1 = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
        json unchangedTransactionList2 = convertToJsonListOfLists(unchangedList2, lastList2, nameForPercentMatching);

            if((standardizedLastList1.find("MATCHED") != string::npos) && (standardizedLastList1.find("UNMATCHED") == string::npos) && (standardizedLastList1.find("PROBABLE") == string::npos)){
                json fullJsonObject = makeJsonObject(unchangedTransactionList1, unchangedTransactionList2, newTransactionList1);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }else{
                json fullJsonObject = makeJsonObject(unchangedTransactionList2, unchangedTransactionList1, newTransactionList1);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }
    }
}

json repairListJson(int idTaken, string tableIdTaken, string listTakenFrom, int idTo, string tableIdTo, string listTakenTo, json inputFile){
    string standardizedListTakenFrom = listTakenFrom;
    string standardizedListTakenTo = listTakenTo;
    string nameForPercentMatching = "percent_matching";
    string nameOfOutputFile = "ChangedOutput.json";

    transform(standardizedListTakenFrom.begin(), standardizedListTakenFrom.end(), standardizedListTakenFrom.begin(), ::toupper);
    transform(standardizedListTakenTo.begin(), standardizedListTakenTo.end(), standardizedListTakenTo.begin(), ::toupper);

    if(standardizedListTakenFrom.find("UNMATCHED") == string::npos && standardizedListTakenTo.find("UNMATCHED") == string::npos){
        list<Transaction> transactionToBeChanged;
        list<list<Transaction>> matchingTrans;

        if(listTakenFrom.compare(listTakenTo) != 0){
            readForAdjustmentsJson(matchingTrans, inputFile, listTakenFrom);

            takeOutTransaction(matchingTrans, transactionToBeChanged, idTaken, tableIdTaken);

            list<list<Transaction>> listToTakeTo;

            readForAdjustmentsJson(listToTakeTo, inputFile, listTakenTo);

            addRelevantTransaction(listToTakeTo, transactionToBeChanged, idTo, tableIdTo);

            list<Transaction> unchangedList;
            string lastList = determineNameOfTheLastListJson(listTakenFrom, listTakenTo, inputFile);

            readForAdjustmentsJson(unchangedList, lastList, inputFile);

            filterToUnmatched(matchingTrans, unchangedList, listToTakeTo);

            json newTransactionList1 = convertToJsonListOfLists(matchingTrans, listTakenFrom, nameForPercentMatching);
            json newTransactionList2 = convertToJsonListOfLists(listToTakeTo, listTakenTo, nameForPercentMatching);
            json unchangedTransactionList = convertToJsonList(unchangedList, lastList);

            if((standardizedListTakenFrom.find("MATCHED") != string::npos) && (standardizedListTakenFrom.find("UNMATCHED") == string::npos) && (standardizedListTakenFrom.find("PROBABLE") == string::npos)){
                json fullJsonObject = makeJsonObject(newTransactionList1, newTransactionList2, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }else{
                json fullJsonObject = makeJsonObject(newTransactionList2, newTransactionList1, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }
        }else{
            readForAdjustmentsJson(matchingTrans, inputFile, listTakenFrom);

            takeOutTransaction(matchingTrans, transactionToBeChanged, idTaken, tableIdTaken);

            addRelevantTransaction(matchingTrans, transactionToBeChanged, idTo, tableIdTo);

            list<list<Transaction>> unchangedList1;
            string lastList1 = determineNameOfTheLastListJson(listTakenFrom, listTakenTo, inputFile);

            readForAdjustmentsJson(unchangedList1, inputFile, lastList1);

            list<Transaction> unchangedList2;
            string lastList2 = determineNameOfTheLastListJson(listTakenFrom, lastList1, inputFile);

            readForAdjustmentsJson(unchangedList2, lastList2, inputFile);

            filterToUnmatched(matchingTrans, unchangedList2, unchangedList1);
            json newTransactionList1 = convertToJsonListOfLists(matchingTrans, listTakenFrom, nameForPercentMatching);
            json unchangedTransactionList2 = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
            json unchangedTransactionList = convertToJsonList(unchangedList2, lastList2);

            if((standardizedListTakenFrom.find("MATCHED") != string::npos) && (standardizedListTakenFrom.find("UNMATCHED") == string::npos) && (standardizedListTakenFrom.find("PROBABLE") == string::npos)){
                json fullJsonObject = makeJsonObject(newTransactionList1, unchangedTransactionList2, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }else{
                json fullJsonObject = makeJsonObject(unchangedTransactionList2, newTransactionList1, unchangedTransactionList);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }
        }
    }else if(standardizedListTakenFrom.find("UNMATCHED") != string::npos && standardizedListTakenTo.find("UNMATCHED") == string::npos){
        list<Transaction> transactionsTobeChanged;
        list<Transaction> unmatchedTrans;

        readForAdjustmentsJson(unmatchedTrans, listTakenFrom, inputFile);

        takeOutTransaction(unmatchedTrans, transactionsTobeChanged, idTaken, tableIdTaken);

        list<list<Transaction>> receivingListOfTransactions;

        readForAdjustmentsJson(receivingListOfTransactions, inputFile, listTakenTo);

        addRelevantTransaction(receivingListOfTransactions, transactionsTobeChanged, idTo, tableIdTo);

        list<list<Transaction>> unchangedList;
        string lastList = determineNameOfTheLastListJson(listTakenFrom, listTakenTo, inputFile);

        readForAdjustmentsJson(unchangedList, inputFile, lastList);

        json newTransactionList1 = convertToJsonListOfLists(receivingListOfTransactions, listTakenTo, nameForPercentMatching);
        json unchangedTransactionList = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
        json newTransactionList2 = convertToJsonList(unmatchedTrans, listTakenFrom);

        if((standardizedListTakenTo.find("MATCHED") != string::npos) && (standardizedListTakenTo.find("UNMATCHED") == string::npos) && (standardizedListTakenTo.find("PROBABLE") == string::npos)){
            json fullJsonObject = makeJsonObject(newTransactionList1, unchangedTransactionList, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }else{
            json fullJsonObject = makeJsonObject(unchangedTransactionList, newTransactionList1, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }
    }else if(standardizedListTakenFrom.find("UNMATCHED") == string::npos && standardizedListTakenTo.find("UNMATCHED") != string::npos){
        list<Transaction> transactionToBeChanged;
        list<list<Transaction>> matchingTrans;

        readForAdjustmentsJson(matchingTrans, inputFile, listTakenFrom);

        takeOutTransaction(matchingTrans, transactionToBeChanged, idTaken, tableIdTaken);

        list<Transaction> listToTakeTo;

        readForAdjustmentsJson(listToTakeTo, listTakenTo, inputFile);

        listToTakeTo.push_back(transactionToBeChanged.front());

        list<list<Transaction>> unchangedList;
        string lastList = determineNameOfTheLastListJson(listTakenFrom, listTakenTo, inputFile);

        readForAdjustmentsJson(unchangedList, inputFile, lastList);

        filterToUnmatched(matchingTrans, listToTakeTo, unchangedList);

        json newTransactionList1 = convertToJsonListOfLists(matchingTrans, listTakenFrom, nameForPercentMatching);
        json unchangedTransactionList = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
        json newTransactionList2 = convertToJsonList(listToTakeTo, listTakenTo);

        if((standardizedListTakenFrom.find("MATCHED") != string::npos) && (standardizedListTakenFrom.find("UNMATCHED") == string::npos) && (standardizedListTakenFrom.find("PROBABLE") == string::npos)){
            json fullJsonObject = makeJsonObject(newTransactionList1, unchangedTransactionList, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }else{
            json fullJsonObject = makeJsonObject(unchangedTransactionList, newTransactionList1, newTransactionList2);

            displayJsonInFile(fullJsonObject, nameOfOutputFile);
            return fullJsonObject;
        }
    }else if(standardizedListTakenFrom.find("UNMATCHED") != string::npos && standardizedListTakenTo.find("UNMATCHED") != string::npos){
        list<Transaction> transactionsToBeChanged;
        list<Transaction> unmatchedTrans;

        readForAdjustmentsJson(unmatchedTrans, listTakenFrom, inputFile);

        list<list<Transaction>> unchangedList1;
        string lastList1 = determineNameOfTheLastListJson(listTakenFrom, listTakenTo, inputFile);
        string standardizedLastList1 = lastList1;
        transform(standardizedLastList1.begin(), standardizedLastList1.end(), standardizedLastList1.begin(), ::toupper);

        readForAdjustmentsJson(unchangedList1, inputFile, lastList1);

        list<list<Transaction>> unchangedList2;
        string lastList2 = determineNameOfTheLastListJson(listTakenFrom, lastList1, inputFile);

        readForAdjustmentsJson(unchangedList2, inputFile, lastList2);

        json newTransactionList1 = convertToJsonList(unmatchedTrans, listTakenFrom);
        json unchangedTransactionList1 = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
        json unchangedTransactionList2 = convertToJsonListOfLists(unchangedList2, lastList2, nameForPercentMatching);

            if((standardizedLastList1.find("MATCHED") != string::npos) && (standardizedLastList1.find("UNMATCHED") == string::npos) && (standardizedLastList1.find("PROBABLE") == string::npos)){
                json fullJsonObject = makeJsonObject(unchangedTransactionList1, unchangedTransactionList2, newTransactionList1);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }else{
                json fullJsonObject = makeJsonObject(unchangedTransactionList2, unchangedTransactionList1, newTransactionList1);

                displayJsonInFile(fullJsonObject, nameOfOutputFile);
                return fullJsonObject;
            }
    }
}

json manuallyMatch(int id1, string tableId1, string list1, int id2, string tableId2, string list2, string input){
    string standardizedList1 = list1;
    string standardizedList2 = list2;
    string nameForPercentMatching = "percent_matching";
    string nameOfOutputFile = "ChangedOutput.json";

    transform(standardizedList1.begin(), standardizedList1.end(), standardizedList1.begin(), ::toupper);
    transform(standardizedList2.begin(), standardizedList2.end(), standardizedList2.begin(), ::toupper);

    if((standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList2.find("UNMATCHED") == string::npos)){
        list<Transaction> newMatchedList;
        
        if(list1.compare(list2) != 0){
            list<list<Transaction>> firstList;
            readForAdjustments(firstList, input, list1);
            takeOutTransaction(firstList, newMatchedList, id1, tableId1);

            list<list<Transaction>> secondList;
            readForAdjustments(secondList, input, list2);
            takeOutTransaction(secondList, newMatchedList, id2, tableId2);

            string lastList = determineNameOfTheLastList(list1, list2, input);
            list<Transaction> unchangedList;
            readForAdjustments(unchangedList, lastList, input);

            filterToUnmatched(firstList, unchangedList, secondList);
            filterToUnmatched(secondList, unchangedList, firstList);

            if((standardizedList1.find("MATCHED") != string::npos) && (standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList1.find("PROBABLE") == string::npos)){
                firstList.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newProbMatchTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList, lastList);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }else{
                secondList.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
                json newProbMatchTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList, lastList);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }
        }else{
            list<list<Transaction>> firstList;
            readForAdjustments(firstList, input, list1);
            takeOutTransaction(firstList, newMatchedList, id1, tableId1);
            takeOutTransaction(firstList, newMatchedList, id2, tableId2);

            string lastList1 = determineNameOfTheLastList(list1, list2, input);
            list<list<Transaction>> unchangedList1;
            readForAdjustments(unchangedList1, input, lastList1);

            string lastList2 = determineNameOfTheLastList(list1, lastList1, input);
            list<Transaction> unchangedList2;
            readForAdjustments(unchangedList2, lastList2, input);

            filterToUnmatched(firstList, unchangedList2, unchangedList1);
            // filterToUnmatched(firstList, unchangedList2, unchangedList1);

            if((standardizedList1.find("MATCHED") != string::npos) && (standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList1.find("PROBABLE") == string::npos)){
                firstList.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newProbMatchedTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList2, lastList2);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }else{
                unchangedList1.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
                json newProbMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList2, lastList2);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }
        }
    }else if((standardizedList1.find("UNMATCHED") != string::npos) && (standardizedList2.find("UNMATCHED") == string::npos)){
        list<Transaction> newMatchedList;

        list<Transaction> firstList;
        readForAdjustments(firstList, list1, input);
        takeOutTransaction(firstList, newMatchedList, id1, tableId1);

        list<list<Transaction>> secondList;
        readForAdjustments(secondList, input, list2);
        takeOutTransaction(secondList, newMatchedList, id2, tableId2);

        string lastList = determineNameOfTheLastList(list1, list2, input);
        list<list<Transaction>> unchangedList;
        readForAdjustments(unchangedList, input, lastList);

        filterToUnmatched(secondList, firstList, unchangedList);

        if((standardizedList2.find("MATCHED") != string::npos) && (standardizedList2.find("UNMATCHED") == string::npos) && (standardizedList2.find("PROBABLE") == string::npos)){
            secondList.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
            json newProbMatchedTransactions = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }else{
            unchangedList.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
            json newProbMatchedTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }
    }else if((standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList2.find("UNMATCHED") != string::npos)){
        list<Transaction> newMatchedList;

        list<list<Transaction>> firstList;
        readForAdjustments(firstList, input, list1);
        takeOutTransaction(firstList, newMatchedList, id1, tableId1);

        list<Transaction> secondList;
        readForAdjustments(secondList, list2, input);
        takeOutTransaction(secondList, newMatchedList, id2, tableId2);

        string lastList = determineNameOfTheLastList(list1, list2, input);
        list<list<Transaction>> unchangedlist;
        readForAdjustments(unchangedlist, input, lastList);

        filterToUnmatched(firstList, secondList, unchangedlist);

        if((standardizedList1.find("MATCHED") != string::npos) && (standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList1.find("PROBABLE") == string::npos)){
            firstList.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(unchangedlist, lastList, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(secondList, list2);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }else{
            unchangedlist.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedlist, lastList, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(secondList, list2);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }
    }else if((standardizedList1.find("UNMATCHED") != string::npos) && (standardizedList2.find("UNMATCHED") != string::npos)){
        list<Transaction> newMatchedList;

        list<Transaction> firstList;
        readForAdjustments(firstList, list1, input);
        takeOutTransaction(firstList, newMatchedList, id1, tableId1);
        takeOutTransaction(firstList, newMatchedList, id2, tableId2);

        string lastList1 = determineNameOfTheLastList(list1, list2, input);
        list<list<Transaction>> unchangedList1;
        readForAdjustments(unchangedList1, input, lastList1);

        string standardizedLastList1 = lastList1;
        transform(standardizedLastList1.begin(), standardizedLastList1.end(), standardizedLastList1.begin(), ::toupper);

        string lastList2 = determineNameOfTheLastList(list1, lastList1, input);
        list<list<Transaction>> unchangedList2;
        readForAdjustments(unchangedList2, input, lastList2);

        if((standardizedLastList1.find("MATCHED") != string::npos) && (standardizedLastList1.find("UNMATCHED") == string::npos) && (standardizedLastList1.find("PROBABLE") == string::npos)){
            unchangedList1.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(unchangedList2, lastList2, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }else{
            unchangedList2.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedList2, lastList2, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }
    }
}

json manuallyMatchJson(int id1, string tableId1, string list1, int id2, string tableId2, string list2, json input){
    string standardizedList1 = list1;
    string standardizedList2 = list2;
    string nameForPercentMatching = "percent_matching";
    string nameOfOutputFile = "ChangedOutput.json";

    transform(standardizedList1.begin(), standardizedList1.end(), standardizedList1.begin(), ::toupper);
    transform(standardizedList2.begin(), standardizedList2.end(), standardizedList2.begin(), ::toupper);

    if((standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList2.find("UNMATCHED") == string::npos)){
        list<Transaction> newMatchedList;
        
        if(list1.compare(list2) != 0){
            list<list<Transaction>> firstList;
            readForAdjustmentsJson(firstList, input, list1);
            takeOutTransaction(firstList, newMatchedList, id1, tableId1);

            list<list<Transaction>> secondList;
            readForAdjustmentsJson(secondList, input, list2);
            takeOutTransaction(secondList, newMatchedList, id2, tableId2);

            string lastList = determineNameOfTheLastListJson(list1, list2, input);
            list<Transaction> unchangedList;
            readForAdjustmentsJson(unchangedList, lastList, input);

            filterToUnmatched(firstList, unchangedList, secondList);
            filterToUnmatched(secondList, unchangedList, firstList);

            if((standardizedList1.find("MATCHED") != string::npos) && (standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList1.find("PROBABLE") == string::npos)){
                firstList.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newProbMatchTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList, lastList);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }else{
                secondList.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
                json newProbMatchTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList, lastList);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }
        }else{
            list<list<Transaction>> firstList;
            readForAdjustmentsJson(firstList, input, list1);
            takeOutTransaction(firstList, newMatchedList, id1, tableId1);
            takeOutTransaction(firstList, newMatchedList, id2, tableId2);

            string lastList1 = determineNameOfTheLastListJson(list1, list2, input);
            list<list<Transaction>> unchangedList1;
            readForAdjustmentsJson(unchangedList1, input, lastList1);

            string lastList2 = determineNameOfTheLastListJson(list1, lastList1, input);
            list<Transaction> unchangedList2;
            readForAdjustmentsJson(unchangedList2, lastList2, input);

            filterToUnmatched(firstList, unchangedList2, unchangedList1);
            // filterToUnmatched(firstList, unchangedList2, unchangedList1);

            if((standardizedList1.find("MATCHED") != string::npos) && (standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList1.find("PROBABLE") == string::npos)){
                firstList.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newProbMatchedTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList2, lastList2);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }else{
                unchangedList1.push_back(newMatchedList);

                json newMatchedTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
                json newProbMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
                json newUnmatchedTransactions = convertToJsonList(unchangedList2, lastList2);

                json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
                displayJsonInFile(fullObject, nameOfOutputFile);
                return fullObject;
            }
        }
    }else if((standardizedList1.find("UNMATCHED") != string::npos) && (standardizedList2.find("UNMATCHED") == string::npos)){
        list<Transaction> newMatchedList;

        list<Transaction> firstList;
        readForAdjustmentsJson(firstList, list1, input);
        takeOutTransaction(firstList, newMatchedList, id1, tableId1);

        list<list<Transaction>> secondList;
        readForAdjustmentsJson(secondList, input, list2);
        takeOutTransaction(secondList, newMatchedList, id2, tableId2);

        string lastList = determineNameOfTheLastListJson(list1, list2, input);
        list<list<Transaction>> unchangedList;
        readForAdjustmentsJson(unchangedList, input, lastList);

        filterToUnmatched(secondList, firstList, unchangedList);

        if((standardizedList2.find("MATCHED") != string::npos) && (standardizedList2.find("UNMATCHED") == string::npos) && (standardizedList2.find("PROBABLE") == string::npos)){
            secondList.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
            json newProbMatchedTransactions = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }else{
            unchangedList.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedList, lastList, nameForPercentMatching);
            json newProbMatchedTransactions = convertToJsonListOfLists(secondList, list2, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchedTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }
    }else if((standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList2.find("UNMATCHED") != string::npos)){
        list<Transaction> newMatchedList;

        list<list<Transaction>> firstList;
        readForAdjustmentsJson(firstList, input, list1);
        takeOutTransaction(firstList, newMatchedList, id1, tableId1);

        list<Transaction> secondList;
        readForAdjustmentsJson(secondList, list2, input);
        takeOutTransaction(secondList, newMatchedList, id2, tableId2);

        string lastList = determineNameOfTheLastListJson(list1, list2, input);
        list<list<Transaction>> unchangedlist;
        readForAdjustmentsJson(unchangedlist, input, lastList);

        filterToUnmatched(firstList, secondList, unchangedlist);

        if((standardizedList1.find("MATCHED") != string::npos) && (standardizedList1.find("UNMATCHED") == string::npos) && (standardizedList1.find("PROBABLE") == string::npos)){
            firstList.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(unchangedlist, lastList, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(secondList, list2);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }else{
            unchangedlist.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedlist, lastList, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(firstList, list1, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(secondList, list2);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }
    }else if((standardizedList1.find("UNMATCHED") != string::npos) && (standardizedList2.find("UNMATCHED") != string::npos)){
        list<Transaction> newMatchedList;

        list<Transaction> firstList;
        readForAdjustmentsJson(firstList, list1, input);
        takeOutTransaction(firstList, newMatchedList, id1, tableId1);
        takeOutTransaction(firstList, newMatchedList, id2, tableId2);

        string lastList1 = determineNameOfTheLastListJson(list1, list2, input);
        list<list<Transaction>> unchangedList1;
        readForAdjustmentsJson(unchangedList1, input, lastList1);

        string standardizedLastList1 = lastList1;
        transform(standardizedLastList1.begin(), standardizedLastList1.end(), standardizedLastList1.begin(), ::toupper);

        string lastList2 = determineNameOfTheLastListJson(list1, lastList1, input);
        list<list<Transaction>> unchangedList2;
        readForAdjustmentsJson(unchangedList2, input, lastList2);

        if((standardizedLastList1.find("MATCHED") != string::npos) && (standardizedLastList1.find("UNMATCHED") == string::npos) && (standardizedLastList1.find("PROBABLE") == string::npos)){
            unchangedList1.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(unchangedList2, lastList2, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }else{
            unchangedList2.push_back(newMatchedList);

            json newMatchedTransactions = convertToJsonListOfLists(unchangedList2, lastList2, nameForPercentMatching);
            json newProbMatchTransactions = convertToJsonListOfLists(unchangedList1, lastList1, nameForPercentMatching);
            json newUnmatchedTransactions = convertToJsonList(firstList, list1);

            json fullObject = makeJsonObject(newMatchedTransactions, newProbMatchTransactions, newUnmatchedTransactions);
            displayJsonInFile(fullObject, nameOfOutputFile);
            return fullObject;
        }
    }
}