#include "Functions.h"

list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction> secondList){
    list<list<Transaction> > matchingTrans;
    for(auto Itr = begin(firstList); Itr != end(firstList); Itr++){
        for(auto Itr2 = begin(secondList); Itr2 != end(secondList); Itr2++){
            if(isMatched(*Itr, *Itr2, PERCENT_TO_MATCH)){
                matchingTrans.push_back(list<Transaction>(1, *Itr));
                matchingTrans.back().push_back(*Itr2);
            }
        }
    }

    return matchingTrans;
}

list<list<Transaction> > probableMatchTransactions(list<Transaction> firstList, list<Transaction> secondList){
    list<list<Transaction> > probableMatchTrans;
    for(auto Itr = begin(firstList); Itr != end(firstList); Itr++){
        for(auto Itr2 = begin(secondList); Itr2 != end(secondList); Itr2++){
            if(isMatched(*Itr, *Itr2, PERCENT_TO_PROB_MATCH) && !isMatched(*Itr, *Itr2, PERCENT_TO_MATCH)){
                probableMatchTrans.push_back(list<Transaction>(1, *Itr));
                probableMatchTrans.back().push_back(*Itr2);
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

void readJsonFile(list<Transaction>& listOfTransaction, string nameOfFile){
    ifstream jsonFile(nameOfFile);
    json dataFromJson;
    jsonFile >> dataFromJson;
    for(const auto& data : dataFromJson["data"]){
        int id = data["id"];
        int value = data["value"];
        string date = data["date"];
        string narration = data["narration"];
        string tableId = dataFromJson["type"];

        listOfTransaction.push_back(Transaction(id, value, date, narration, tableId));
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
                subMatchedTransaction.push_back(json{{nameForPercentMatching, percentMatching(*itr2, *(--itr4))}});
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

void getMatchedProbableMatchAndUnmatched(string firstFileToReadFrom, string secondFileToReadFrom, string fileToOutputTo, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions, string nameForPercentageMatched){
    list<Transaction> firstList;
    list<Transaction> secondList;

    readJsonFile(firstList, firstFileToReadFrom);
    readJsonFile(secondList, secondFileToReadFrom);

    list<list<Transaction>> matchedTransactions = matchTransactions(firstList, secondList);
    list<list<Transaction>> probableMatchedTransactions = probableMatchTransactions(firstList, secondList);
    list<Transaction> unmatchedTransactions = unmatchTransactions(firstList, secondList);

    json jsonMatchedTransactions = convertToJsonListOfLists(matchedTransactions, nameForMatchedTransactions, nameForPercentageMatched);
    json jsonProbableMatchedTransactions = convertToJsonListOfLists(probableMatchedTransactions, nameForProbableMacthedTransactions, nameForPercentageMatched);
    json jsonUnmatchedTransactions = convertToJsonList(unmatchedTransactions, nameForUnmatchedTransactions);

    json combinedJsonObject = makeJsonObject(jsonMatchedTransactions, jsonProbableMatchedTransactions, jsonUnmatchedTransactions);

    ofstream outputFile(fileToOutputTo);

    outputFile << combinedJsonObject.dump(4);
    outputFile.close();
}