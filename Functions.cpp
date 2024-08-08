#include "Functions.h"

list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction> secondList){
    list<list<Transaction> > matchingTrans;
    for(auto Itr = begin(firstList); Itr != end(firstList); Itr++){
        auto Itr2 = begin(secondList);
        for(; Itr2 != end(secondList); Itr2++){
            if((Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), 0) && (Itr->getNarration().compare(Itr2->getNarration()) == 0)){
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
        auto Itr2 = begin(secondList);
        for(; Itr2 != end(secondList); Itr2++){
            if(((Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), DAYS_TO_MATCH) && relatedNarration(Itr->getNarration(), Itr2->getNarration()))
            && !((Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), 0) && (Itr->getNarration().compare(Itr2->getNarration()) == 0))){
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
            if(((Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), DAYS_TO_MATCH) && relatedNarration(Itr->getNarration(), Itr2->getNarration()))
            || ((Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), 0) && (Itr->getNarration().compare(Itr2->getNarration()) == 0))){
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
            if((Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), DAYS_TO_MATCH) && relatedNarration(Itr->getNarration(), Itr2->getNarration())
            || (Itr->getVal() == Itr2->getVal()) && withinDateRange(Itr->getDate(), Itr2->getDate(), 0) && (Itr->getNarration().compare(Itr2->getNarration()) == 0)){
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
    int yearOfDate1 = stoi(date1.substr(6, 4));
    int monthOfDate1 = stoi(date1.substr(3, 2));
    int dayfDate1 = stoi(date1.substr(0, 2));
    int yearOfDate2 = stoi(date2.substr(6, 4));
    int monthOfDate2 = stoi(date2.substr(3, 2));
    int dayfDate2 = stoi(date2.substr(0, 2));

    int diffDate = abs((yearOfDate1 - yearOfDate2) * DAYS_IN_YEAR) + abs((monthOfDate1 - monthOfDate2) * DAYS_IN_MONTH) + abs(dayfDate1 - dayfDate2);
    return diffDate;
}

bool withinDateRange(string date1, string date2, int days){
    return (diffDates(date1, date2) <= days);
}

bool relatedNarration(string narration1, string narration2){
    transform(narration1.begin(), narration1.end(), narration1.begin(), ::tolower);
    transform(narration2.begin(), narration2.end(), narration2.begin(), ::tolower);

    list<string> narrationSplit1;
    list<string> narrationSplit2;

    int numberOfMatches = 0;
    list<string> firstSeparation = splitString(narration1, ' ');
    list<string> secondSeparation = splitString(narration2, ' ');
    for(auto itr = begin(firstSeparation); itr != end(firstSeparation); itr++){
        for(auto itr2 = begin(secondSeparation); itr2 != end(secondSeparation); itr2++){
            if((*itr).compare(*itr2) == 0){
                numberOfMatches++;
                break;
            }
        }
    }

    if (numberOfMatches >= WORDS_TO_MATCH){
        return true;
    }else{
        return false;
    }
}

void display(list<list<Transaction> > matchedTransactions){
    cout << "[" << ends;
    for(auto itr = begin(matchedTransactions); itr != end(matchedTransactions); itr++){
        cout << "[" << ends;
        for(auto itr2 = begin(*itr); itr2 != end(*itr); itr2++){
            auto itr3 = itr2;
            if((++itr3) == end(*itr)){
                cout << itr2->getNarration() << ends;
            }else{
                cout << itr2->getNarration() << ", " << ends;
            }
        }
        auto itr4 = itr;
        if((++itr4) == end(matchedTransactions)){
            cout << "]" << ends;
        }else{
            cout << "]," << ends;
        }
    }
    cout << "]" << endl;
}

void display(list<Transaction> unmatchedTransactions){
    cout << "[" << ends;
    for(auto itr = begin(unmatchedTransactions); itr != end(unmatchedTransactions); itr++){
        auto itr2 = itr;
        if((++itr2) == end(unmatchedTransactions)){
            cout << itr->getNarration() << ends;
        }else{
            cout << itr->getNarration() << ", " << ends;
        }
    }
    cout << "]" << endl;
}

void sortTransactions(list<Transaction>& destinationArray1, list<Transaction>& destinationArray2, list<Transaction> sourceArray){
    for(auto itr = begin(sourceArray); itr != end(sourceArray); itr++){
        if(itr->getArrayId() == 1){
            destinationArray1.push_back(*itr);
        }else if(itr->getArrayId() == 2){
            destinationArray2.push_back(*itr);
        }
    }
}

list<string> splitString(string sentence, char seperator){
    int i = 0;  
    int startIndex = 0;
    int endIndex = 0;
    list<string> splitStr;
    bool containsSep = false;
    if(sentence.find(' ') != string::npos){
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