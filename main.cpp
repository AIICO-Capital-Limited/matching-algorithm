#include <iostream>
#include <list>
#include "Transaction.h"
#include "Functions.h"

using namespace std;

int main(){

    //Initializing two json lists to read from
    json array1 = json::array();
    array1.push_back({
            {"id", 231},
            {"value", 300},
            {"date", "12/03/2024"},
            {"narration", "Payment received from client A"}
        });
    array1.push_back({
            {"id", 756},
            {"value", 249.99},
            {"date", "25/07/2023"},
            {"narration", "Office supplies purchase"}
        });
    array1.push_back({
            {"id", 128},
            {"value", 659.88},
            {"date", "05/10/2023"},
            {"narration", "Monthly subscription renewal"}
        });
    
    json firstList = {
    {"type","Bank"},
    {"data", array1}
    };

    json array2 = json::array();
    array2.push_back({
            {"id", 354},
            {"value", 300},
            {"date", "17/03/2024"},
            {"narration", "Funds received from client A"}
        });
    array2.push_back({
            {"id", 912},
            {"value", 249.99},
            {"date", "28/07/2023"},
            {"narration", "Purchase of office supplies"}
        });
    array2.push_back({
            {"id", 487},
            {"value", 659.88},
            {"date", "10/10/2023"},
            {"narration", "Renewal of monthly subscription"}
        
        });
    json secondList = {
        {"type", "GL"},
        {"data", array2}
    };


    //Initializing the organizedTransactions json objiect
    json array3 = json::array();
    array3.push_back({
                {"date", "12/03/2024"},
                {"id", 231},
                {"narration", "Payment received from client A"},
                {"table_ID", "Bank"},
                {"value", 300.0}
            });
    array3.push_back({
                {"date", "17/03/2024"},
                {"id", 354},
                {"narration", "Funds received from client A"},
                {"table_ID", "GL"},
                {"value", 300.0}
            });
    array3.push_back({
                {"percent_matching", 60.0}
            });
    
    json array4 = json::array();
    array4.push_back({
                {"date", "25/07/2023"},
                {"id", 756},
                {"narration", "Office supplies purchase"},
                {"table_ID", "Bank"},
                {"value", 249.99}
            });
    array4.push_back({
                {"date", "28/07/2023"},
                {"id", 912},
                {"narration", "Purchase of office supplies"},
                {"table_ID", "GL"},
                {"value", 249.99}
            });
    array4.push_back({
                {"percent_matching", 58.333333333333336}
            });

    json array9 = json::array();
    array9.push_back(array3);
    array9.push_back(array4);

    json array5 = json::array();
    json array6 = json::array();

    array6.push_back(array5);

    json array7 = json::array();
    json array8 = json::array();

    json organizedTransactions = {
        {"matched_transaction", array6},
        {"probable_matches", array9},
        {"unmatched_transactions", array8}
    };

    //Operations on both files and json objects
    // getMatchedProbableMatchAndUnmatched("bank.json", "gl.json", "output.json", "matched_transaction", "probable_matches", "unmatched_transactions");
    // getMatchedProbableMatchAndUnmatchedFromJsonLists(firstList, secondList, "output.json", "matched_transaction", "probable_matches", "unmatched_transactions");
    // repairList(338, "GL", "probable_matches", 542, "Bank", "matched_transaction", "output.json");
    // repairListJson(912, "GL", "probable_matches", 354, "GL", "probable_matches", organizedTransactions);
    // manuallyMatch(690, "GL", "matched_transaction", 392, "Bank", "matched_transaction", "output.json");
    manuallyMatchJson(912, "GL", "probable_matches", 231, "Bank", "probable_matches", organizedTransactions);
    
    return 0;
}