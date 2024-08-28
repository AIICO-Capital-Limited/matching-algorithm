#include <iostream>
#include "Functions.h"

int main(){
    getMatchedProbableMatchAndUnmatched("GL3.json", "Bank3.json", "output.json", "matched_transactions", "probable_matches", "unmatched_transactions");
    // repairList(165, "Bank", "probable_matches", 152, "Bank", "probable_matches", "ChangedOutput.json");
    // manuallyMatch(64, "GL", "probable_matches", 169, "Bank", "probable_matches", "output.json");

    return 0;
}