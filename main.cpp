#include <iostream>
#include "Functions.h"

int main(){
    string firstList = "{ \"type\": \"GL\",\"data\": [{\"GL PostDate\": \" 31-03-2024\",\"date\": \"31-03-2024\",\"VoucherNo\": \"\",\"narration\": \"Balance b/f\",\"id\": 1,\"debit\": 635652.16,\"credit\": 0,\"balance\": 635652.16,\"Forex_Amt(dr)\": 0,\"Forex_Amt(cr)\": 0,\"ExcRate\": 1},{\"GL PostDate\": \" 05-04-2024\",\"date\": \"05-04-2024\",\"VoucherNo\": \"GL00010403\",\"narration\": \"EB CLIENTS CAKE PYT   B9986837250T 0000122404051600 EB CLIENTS CAKE RBX 99868372509986837252 GTB AWOH  DEBORAH KEUOJOR\",\"id\": 2,\"debit\": 0,\"credit\": 40000,\"balance\": 595652.16,\"Forex_Amt(dr)\": 0,\"Forex_Amt(cr)\": 0,\"ExcRate\": 1}]}";
    string secondList = "{\"type\": \"Bank\",\"data\": [{\"id\": 1,\"Transaction Date\": \"\",\"date\": \"01/06/2024\",\"narration\": \"Opening Balance\",\"Type\": \"\",\"debit\": 0,\"credit\": 0,\"balance\": 1708910.51},{\"id\": 2,\"Transaction Date\": \"06/03/2024\",\"date\": \"03/06/2024\",\"narration\": \"0029596554UBNG03 06 24 TRF UBNG03 06 24 TRF 0029596554UBNG03 AIICO CAPITAL LIMITED-MANAGED FUND\",\"Type\": \"TRF\",\"debit\": 0,\"credit\": 15000000,\"balance\": 16708910.51}, {\"GL PostDate\": \" 05-04-2024\",\"date\": \"05-04-2024\",\"VoucherNo\": \"GL00010656\",\"narration\": \"R/E: EB CLIENTS CAKE PYT   B9986837250T 0000122404051600 EB CLIENTS CAKE RBX 99868372509986837252 GTB AWOH  DEBORAH KEUOJOR\",\"id\": 3,\"debit\": 40000,\"credit\": 0,\"balance\": 635652.16,\"Forex_Amt(dr)\": 0,\"Forex_Amt(cr)\": 0,\"ExcRate\": 1}]}";
    // getMatchedProbableMatchAndUnmatched("GL3.json", "Bank3.json", "output.json", "matched_transactions", "probable_matches", "unmatched_transactions");
    cout << getMatchedProbableMatchAndUnmatchedFromJsonLists(firstList, secondList, "matched_transactions", "probable_matches", "unmatched_transactions") << endl;
    // repairList(165, "Bank", "probable_matches", 152, "Bank", "probable_matches", "ChangedOutput.json");
    // manuallyMatch(64, "GL", "probable_matches", 169, "Bank", "probable_matches", "output.json");

    return 0;
}