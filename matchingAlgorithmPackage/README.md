# README

---

# IMPORTANT
To use the API in a Javascript project you need to require it e.g. `const addon = require('./matchingAlgorithmPackage/build/Release/addon')` and the package needs to be in the same folder as the JavaScript project. You may rename the package but be sure to change the name in the path also. DO NOT RENAME any other folder or file within the package.

The functions callable from the Jvascript functions are:
- `setPercentToMatch(int)`: That takes an int and sets the percent for the transactions to be considered matched transactions.
- `setPercentToProbMatch(int)`: That takes an int and sets the percent for the transactions to be considered probably matched.
- `setDaysToMatch(int)`: That takes an int and sets the days for a transaction to be considered a match. If the days between two transactions are more than this set date, then the percentage matching for days is 0 the formula for percent day matching is 100 - ((differece in days between two transactions) * (100)/(days for transaction to be considered a match))
- `matchTransactions(string, string, string, string, string)`: That takes the firstlist of transactions as a Json, the second List of transactions, the name for the matched transactions, the name for the probable matched transactions and the name for the unmatched transactions respectively and performs the operation returnig a json as a string which can then be parsed to a json in the java project.
- `repairMatches(int, string, string, int, string, string, json string)`: That takes in the id, table id and current list, of the transaction whose location is to be changed, and then the id, table id, and list of any transaction in the desired location of the transaction and then the json as a string of the most recent grouping of transactions and then returns a json as a string of the new grouping of transactions which can then be parsed into a json.
- `manuallyMatch(int, string, string, int, string, string, json string)`: That takes in the id, table id and current list, of the first transaction whose location is to be changed, and then the id, table id, and list of the other transaction to be matched with the first and then the json as a string of the most recent grouping of transactions and then returns a json as a string of the new grouping of transactions which can then be parsed into a json.

There is a file called Test.js in the package with an exampe of how to use these functions. You may delete the file from within the package.
---

## Overview

Below you can find a brief description of all the includes and functions in the `Functions.h` header file.

## Includes

The project makes use of the following C++ standard library headers:

- `<iostream>`: Provides functionality for input and output stream operations.
- `<ctime>`: Includes functions for working with date and time.
- `<string>`: Offers support for string manipulation.
- `<list>`: Implements a doubly linked list container.
- `<fstream>`: Facilitates file input and output operations.
- `<stdexcept>`: Provides standard exception classes for error handling.

Additionally, the project uses the Nlohmann JSON library:

- `nlohmann/json.hpp`: A header-only library for JSON serialization and deserialization. It simplifies working with JSON data by providing an easy-to-use interface for parsing and generating JSON.

## Constants

The following constants are used throughout the project:

- `const int DAYS_TO_MATCH;`  
  Specifies the number of days required to consider a match.

- `const int PERCENT_TO_MATCH;`  
  Defines the percentage threshold to determine a match.

- `const int PERCENT_TO_PROB_MATCH;`  
  Sets the percentage threshold for a probable match.

- `const string MATCHED_TEXT;`  
  The text representation for a confirmed match.

- `const string PROBABLE_TEXT;`  
  The text representation for a probable match.

- `const string UNMATCHED_TEXT;`  
  The text representation for no match.

- `const string PERCENT_MATCHING_TEXT;`  
  The key used to represent the percentage matching in JSON data.

## Transaction Class

The `Transaction` class represents a financial transaction with several attributes and provides methods to access and display these attributes. 

### Attributes

- `int id`: The unique identifier for the transaction.
- `double value`: The monetary value of the transaction.
- `string date`: The date of the transaction.
- `string narration`: A description or note related to the transaction.
- `string tableId`: An identifier for the table or category associated with the transaction.

### Methods

- `Transaction(int id, double value, string date, string narration, string tableId)`: Constructor to initialize a `Transaction` object with specified attributes.

- `int getId()`: Returns the unique identifier of the transaction.

- `double getVal()`: Returns the monetary value of the transaction.

- `string getDate()`: Returns the date of the transaction.

- `string getNarration()`: Returns the narration of the transaction.

- `string getTableId()`: Returns the table ID associated with the transaction.

- `void toString()`: Prints a textual representation of the transaction in a formatted manner.

- `json toJson() const`: Converts the transaction object to a JSON object with attributes "id", "value", "date", "narration", and "table_ID".

## Functions

### `list<list<Transaction> > matchTransactions(list<Transaction> firstList, list<Transaction>& secondList)`

This function identifies and groups matching transactions from two lists based on a percentage similarity threshold. 

#### Parameters

- `list<Transaction> firstList`: The first list of transactions to be compared.
- `list<Transaction>& secondList`: The second list of transactions to be compared.

#### Returns

- `list<list<Transaction>>`: A list of lists, where each sublist contains transactions that are considered a match based on the specified percentage threshold.

#### Description

1. **Initial Matching**: The function iterates through `firstList` and compares each transaction with those in `secondList`. If a match is found based on the `PERCENT_TO_MATCH` threshold, the transaction is added to `transactionsThatHaveMatches`.

2. **Sub-Matching**: For each transaction in `transactionsThatHaveMatches`, it finds other transactions in `secondList` that match the current transaction based on the same percentage threshold. Matches are collected in `subMatches` and added to the `matchingTrans` list.

3. **Refinement**: The function refines the matches by comparing the percent matching between transactions in different sublists. Transactions are reallocated to sublists to optimize the grouping based on the highest match percentage.

4. **Return**: The refined list of transaction groups (`matchingTrans`) is returned.

---

### `list<list<Transaction> > probableMatchTransactions(list<Transaction> firstList, list<Transaction> secondList)`

This function identifies and groups transactions from two lists that have a probable match based on a lower percentage similarity threshold. 

#### Parameters

- `list<Transaction> firstList`: The first list of transactions to be compared.
- `list<Transaction> secondList`: The second list of transactions to be compared.

#### Returns

- `list<list<Transaction>>`: A list of lists, where each sublist contains transactions that have a probable match based on the specified percentage threshold.

#### Description

1. **Initial Probable Matching**: The function iterates through `firstList` and compares each transaction with those in `secondList`. If a probable match is found based on the `PERCENT_TO_PROB_MATCH` threshold and it does not meet the `PERCENT_TO_MATCH` threshold, the transaction is added to `transactionsThatHaveMatches`.

2. **Sub-Probable Matching**: For each transaction in `transactionsThatHaveMatches`, it finds other transactions in `secondList` that have a probable match with the current transaction. These transactions are collected in `subProbMatches` and added to the `probableMatchTrans` list.

3. **Refinement**: Similar to the `matchTransactions` function, this step refines the probable matches by comparing the percent matching between transactions in different sublists. Transactions are reallocated to sublists based on the highest match percentage.

4. **Return**: The refined list of probable match transaction groups (`probableMatchTrans`) is returned.

---

### `list<Transaction> unmatchTransactions(list<Transaction> firstList, list<Transaction> secondList)`

This function identifies transactions from two lists that do not have any match based on the specified percentage similarity thresholds.

#### Parameters

- `list<Transaction> firstList`: The first list of transactions to be compared.
- `list<Transaction> secondList`: The second list of transactions to be compared.

#### Returns

- `list<Transaction>`: A list of transactions that are unmatched in both lists based on the specified percentage thresholds.

#### Description

1. **Find Unmatched Transactions in `firstList`**: The function iterates through `firstList` and checks if each transaction has any matching transactions in `secondList` based on either the `PERCENT_TO_PROB_MATCH` or `PERCENT_TO_MATCH` thresholds. Transactions with no matches are added to `unmatchedTrans`.

2. **Find Unmatched Transactions in `secondList`**: The function then performs a similar check for transactions in `secondList` against `firstList`. Transactions with no matches are also added to `unmatchedTrans`.

3. **Return**: The list of unmatched transactions (`unmatchedTrans`) from both lists is returned.

---

### `int diffDates(string date1, string date2)`

This function calculates the absolute difference in days between two dates.

#### Parameters

- `string date1`: The first date in `DD-MM-YYYY` format.
- `string date2`: The second date in `DD-MM-YYYY` format.

#### Returns

- `int`: The absolute difference in days between `date1` and `date2`.

#### Description

1. **Parse Dates**: The function extracts the day, month, and year from both date strings.

2. **Calculate Day Count**: It computes the total number of days from a base reference (considering leap years) for both dates.

3. **Calculate Difference**: The difference in days between the two computed day counts is calculated and returned.

### `double withinDateRange(string date1, string date2)`

This function calculates the percentage of match between two dates based on their difference relative to a predefined number of days.

#### Parameters

- `string date1`: The first date in `DD-MM-YYYY` format.
- `string date2`: The second date in `DD-MM-YYYY` format.

#### Returns

- `double`: The percentage indicating how close the two dates are, based on the difference in days relative to `DAYS_TO_MATCH`. Returns `0.0` if the percentage is negative.

#### Description

1. **Calculate Percentage Match**: The function computes the percentage of date match by subtracting the percentage of days difference (relative to `DAYS_TO_MATCH`) from 100.

2. **Ensure Non-Negative Result**: It ensures that the percentage is not negative, returning `0.0` if the computed percentage is below zero.

---

### `double relatedNarration(string narration1, string narration2)`

Calculates the percentage of similarity between two narration strings by comparing their words.

#### Parameters

- `string narration1`: The first narration string.
- `string narration2`: The second narration string.

#### Returns

- `double`: The percentage of matching words between the two narration strings, considering case insensitivity and ignoring punctuation.

#### Description

1. **Normalize Case**: Converts both narration strings to lowercase for case-insensitive comparison.
2. **Split Strings**: Splits each narration string into words.
3. **Count Matches**: Counts the number of matching words between the two sets of words.
4. **Calculate Percentage**: Computes the percentage of matches based on the size of the larger set of words and returns this percentage.

---

### `void display(list<list<Transaction>> matchedTransactions)`

Displays a formatted output of matched transactions.

#### Parameters

- `list<list<Transaction>> matchedTransactions`: A list of lists of matched transactions.

#### Description

1. **Iterate Through Lists**: Loops through each list of matched transactions.
2. **Display Transactions**: Outputs each transaction's details and the percentage matching between consecutive transactions in the list.
3. **Format Output**: Formats the output as nested lists with appropriate separators and labels.

---

### `void display(list<Transaction> unmatchedTransactions)`

Displays a formatted output of unmatched transactions.

#### Parameters

- `list<Transaction> unmatchedTransactions`: A list of unmatched transactions.

#### Description

1. **Iterate Through Transactions**: Loops through each transaction in the list.
2. **Display Transactions**: Outputs each transaction's details.
3. **Format Output**: Formats the output as a list with appropriate separators and labels.

---

### `list<string> splitString(string sentence, char separator)`

Splits a string into a list of substrings based on a specified separator, ignoring punctuation.

#### Parameters

- `string sentence`: The string to be split.
- `char separator`: The character used to separate substrings.

#### Returns

- `list<string>`: A list of substrings obtained by splitting the input string.

#### Description

1. **Normalize and Remove Punctuation**: Converts the string to lowercase and removes punctuation.
2. **Split String**: Splits the cleaned string into substrings based on the separator.
3. **Return Result**: Returns the list of substrings.

---

### `bool isMatched(Transaction transaction1, Transaction transaction2, int percentToMatch)`

Determines if two transactions match based on a percentage similarity threshold.

#### Parameters

- `Transaction transaction1`: The first transaction.
- `Transaction transaction2`: The second transaction.
- `int percentToMatch`: The percentage similarity threshold.

#### Returns

- `bool`: `true` if the percentage matching between the two transactions meets or exceeds the threshold; otherwise, `false`.

#### Description

1. **Calculate Matching Percentage**: Uses `percentMatching` to determine the percentage similarity between the two transactions.
2. **Compare with Threshold**: Compares the calculated percentage with the specified threshold and returns the result.

---

### `double percentMatching(Transaction transaction1, Transaction transaction2)`

Calculates the average percentage of similarity between two transactions based on value, date, and narration.

#### Parameters

- `Transaction transaction1`: The first transaction.
- `Transaction transaction2`: The second transaction.

#### Returns

- `double`: The average percentage of similarity between the two transactions.

#### Description

1. **Calculate Individual Matches**: Computes the match percentage for value, date, and narration.
2. **Average Match**: Calculates the average percentage of these individual matches and returns it.

---

### `double averagePercentMatching(list<Transaction> matchingTransactions)`

Calculates the average percentage of similarity among a list of transactions.

#### Parameters

- `list<Transaction> matchingTransactions`: A list of transactions to compare.

#### Returns

- `double`: The average percentage of similarity between the transactions in the list.

#### Description

1. **Compute Total Match Percentage**: Loops through the transactions, computes the matching percentage between each pair, and accumulates the total.
2. **Calculate Average**: Computes the average percentage based on the total match percentages and returns it.

---

### `void filterToUnmatched(list<list<Transaction>>& matchingTransactions, list<Transaction>& unmatchedTransactions, list<list<Transaction>>& otherList)`

Filters out transactions that are uniquely matched in `matchingTransactions` and adds them to `unmatchedTransactions` if they do not exist in `otherList`.

#### Parameters

- `list<list<Transaction>>& matchingTransactions`: The list of matched transaction groups.
- `list<Transaction>& unmatchedTransactions`: The list to store unmatched transactions.
- `list<list<Transaction>>& otherList`: The list of other transactions to compare against.

#### Description

1. **Check Unique Matches**: Identifies groups of transactions with a single match.
2. **Validate Against Other List**: Checks if these unique matches exist in `otherList`.
3. **Update Lists**: Moves unmatched transactions to `unmatchedTransactions` and removes them from `matchingTransactions`.

---

### `void filterMultipleToUnmatched(list<list<Transaction>>& matchingTransactions, list<Transaction>& unmatchTransactions, list<list<Transaction>> otherList)`

Filters out transactions from `matchingTransactions` that do not have a matching `tableId` in `otherList` and adds them to `unmatchTransactions`.

#### Parameters

- `list<list<Transaction>>& matchingTransactions`: The list of matched transaction groups.
- `list<Transaction>& unmatchTransactions`: The list to store unmatched transactions.
- `list<list<Transaction>> otherList`: The list of other transactions to compare against.

#### Description

1. **Check Table IDs**: Identifies groups of transactions where the `tableId` does not match with the `tableId` of transactions in `otherList`.
2. **Move Unmatched**: Moves transactions with mismatched `tableId` to `unmatchTransactions` and removes them from `matchingTransactions`.

---

### `void readJsonFile(list<Transaction>& listOfTransaction, string nameOfFile)`

Reads a JSON file and populates a list of transactions based on the file's contents.

#### Parameters

- `list<Transaction>& listOfTransaction`: The list to be populated with transactions.
- `string nameOfFile`: The name of the JSON file to read.

#### Description

1. **Open File**: Opens the specified JSON file.
2. **Parse JSON Data**: Reads and parses the JSON data.
3. **Populate List**: Creates `Transaction` objects from the parsed data and adds them to `listOfTransaction`.

---

### `void readJsonArray(list<Transaction>& listOfTransactions, const json& jsonArray)`

Reads a JSON array and populates a list of transactions based on the array's contents.

#### Parameters

- `list<Transaction>& listOfTransactions`: The list to be populated with transactions.
- `const json& jsonArray`: The JSON array to read from.

#### Description

1. **Parse JSON Array**: Reads and parses the JSON array.
2. **Populate List**: Creates `Transaction` objects from the parsed data and adds them to `listOfTransactions`.

---

### `json convertToJsonListOfLists(list<list<Transaction>> Transactions, string name, string nameForPercentMatching)`

Converts a list of lists of transactions into a JSON object with matching percentages.

#### Parameters

- `list<list<Transaction>> Transactions`: The list of lists of transactions to convert.
- `string name`: The key for the JSON object.
- `string nameForPercentMatching`: The key for the percentage matching values.

#### Returns

- `json`: The JSON object representing the list of transactions and their matching percentages.

#### Description

1. **Format Transactions**: Converts each list of transactions into a JSON array with transaction details and percentage matching.
2. **Create JSON Object**: Creates a JSON object with the specified name and the formatted transaction data.
3. **Return Result**: Returns the constructed JSON object.

---

### `json convertToJsonList(list<Transaction> Transaction, string name)`

Converts a list of transactions into a JSON object with a specified key.

#### Parameters

- `list<Transaction> Transaction`: The list of transactions to convert.
- `string name`: The key for the JSON object.

#### Returns

- `json`: The JSON object containing the list of transactions.

#### Description

1. **Format Transactions**: Converts each transaction into its JSON representation.
2. **Create JSON Object**: Creates a JSON object with the specified key and the formatted transaction data.
3. **Return Result**: Returns the constructed JSON object.

---

### `json makeJsonObject(json firstList, json secondList, json thirdList)`

Creates a JSON object combining three JSON lists.

#### Parameters

- `json firstList`: The first JSON list.
- `json secondList`: The second JSON list.
- `json thirdList`: The third JSON list.

#### Returns

- `json`: The JSON object containing the three JSON lists.

#### Description

1. **Combine Lists**: Combines the three provided JSON lists into a single JSON object.
2. **Return Result**: Returns the combined JSON object.

---

### `int countLeapYearDays(int d[])`

Counts the number of leap year days up to a given year.

#### Parameters

- `int d[]`: An array where `d[2]` represents the year and `d[1]` represents the month.

#### Returns

- `int`: The number of leap year days up to the given year.

#### Description

1. **Adjust Year**: Decreases the year if the month is January or February.
2. **Count Leap Years**: Calculates the number of leap years up to the adjusted year using standard leap year rules.

---

### `json getMatchedProbableMatchAndUnmatched(string firstFileToReadFrom, string secondFileToReadFrom, string fileToOutputTo, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions)`

Processes two JSON files to find matched, probable matched, and unmatched transactions, then outputs the results to a file.

#### Parameters

- `string firstFileToReadFrom`: The name of the first JSON file to read.
- `string secondFileToReadFrom`: The name of the second JSON file to read.
- `string fileToOutputTo`: The name of the file to output the JSON result.
- `string nameForMatchedTransactions`: The key for matched transactions in the output JSON.
- `string nameForProbableMacthedTransactions`: The key for probable matched transactions in the output JSON.
- `string nameForUnmatchedTransactions`: The key for unmatched transactions in the output JSON.

#### Returns

- `json`: The combined JSON object containing matched, probable matched, and unmatched transactions.

#### Description

1. **Read Files**: Reads transactions from the specified JSON files.
2. **Match Transactions**: Finds matched, probable matched, and unmatched transactions.
3. **Filter Results**: Filters the transactions to determine unmatched and probable matched transactions.
4. **Create JSON Objects**: Converts the results to JSON format.
5. **Write to File**: Outputs the combined JSON object to the specified file.

---

### `json getMatchedProbableMatchAndUnmatchedFromJsonLists(json firstJsonToReadFrom, json secondJsonToReadFrom, string nameForMatchedTransactions, string nameForProbableMacthedTransactions, string nameForUnmatchedTransactions)`

Processes two JSON objects to find matched, probable matched, and unmatched transactions.

#### Parameters

- `json firstJsonToReadFrom`: The first JSON object to read.
- `json secondJsonToReadFrom`: The second JSON object to read.
- `string nameForMatchedTransactions`: The key for matched transactions in the output JSON.
- `string nameForProbableMacthedTransactions`: The key for probable matched transactions in the output JSON.
- `string nameForUnmatchedTransactions`: The key for unmatched transactions in the output JSON.

#### Returns

- `json`: The combined JSON object containing matched, probable matched, and unmatched transactions.

#### Description

1. **Read JSON Objects**: Parses transactions from the provided JSON objects.
2. **Match Transactions**: Finds matched, probable matched, and unmatched transactions.
3. **Filter Results**: Filters the transactions to determine unmatched and probable matched transactions.
4. **Create JSON Objects**: Converts the results to JSON format.

---

### `void readForAdjustments(list<list<Transaction>>& listOfTransactions, string inputFile, string nameOfTable)`

Reads transactions from a JSON file and populates a list of transaction groups.

#### Parameters

- `list<list<Transaction>>& listOfTransactions`: The list to be populated with transaction groups.
- `string inputFile`: The name of the JSON file to read.
- `string nameOfTable`: The key in the JSON file for the transactions.

#### Description

1. **Open File**: Opens and reads the specified JSON file.
2. **Parse Data**: Extracts and processes transaction groups based on the specified key.
3. **Populate List**: Adds the transaction groups to `listOfTransactions`.

---

### `void readForAdjustments(list<Transaction>& listOfTransactions, string nameOfTable, string inputFile)`

Reads transactions from a JSON file and populates a single list of transactions.

#### Parameters

- `list<Transaction>& listOfTransactions`: The list to be populated with transactions.
- `string nameOfTable`: The key in the JSON file for the transactions.
- `string inputFile`: The name of the JSON file to read.

#### Description

1. **Open File**: Opens and reads the specified JSON file.
2. **Parse Data**: Extracts and processes transactions based on the specified key.
3. **Populate List**: Adds the transactions to `listOfTransactions`.

---

### `void readForAdjustmentsJson(list<list<Transaction>>& listOfTransactions, json jsonObject, string nameOfTable)`

Reads transaction groups from a JSON object and populates a list of transaction groups.

#### Parameters

- `list<list<Transaction>>& listOfTransactions`: The list to be populated with transaction groups.
- `json jsonObject`: The JSON object to read from.
- `string nameOfTable`: The key in the JSON object for the transactions.

#### Description

1. **Parse Data**: Extracts and processes transaction groups from the JSON object based on the specified key.
2. **Populate List**: Adds the transaction groups to `listOfTransactions`.

---

### `void readForAdjustmentsJson(list<Transaction>& listOfTransactions, string nameOfTable, json jsonObject)`

Reads transactions from a JSON object and populates a single list of transactions.

#### Parameters

- `list<Transaction>& listOfTransactions`: The list to be populated with transactions.
- `string nameOfTable`: The key in the JSON object for the transactions.
- `json jsonObject`: The JSON object to read from.

#### Description

1. **Parse Data**: Extracts and processes transactions from the JSON object based on the specified key.
2. **Populate List**: Adds the transactions to `listOfTransactions`.

---

### `string determineNameOfTheLastList(string listTakenFrom, string listTakenTo, string inputFile)`

Determines the name of the last list in a JSON file that is not one of the specified lists.

#### Parameters

- `string listTakenFrom`: The name of the first list to exclude.
- `string listTakenTo`: The name of the second list to exclude.
- `string inputFile`: The name of the JSON file to read.

#### Returns

- `string`: The name of the last list that is not one of the excluded lists.

#### Description

1. **Open File**: Opens and reads the specified JSON file.
2. **Find Last List**: Searches for the first list in the JSON file that is not excluded by the given names.
3. **Return Result**: Returns the name of this last list.

---

### `string determineNameOfTheLastListJson(string listTakenFrom, string listTakenTo, json inputFile)`

Determines the name of the last list in a JSON object that is not one of the specified lists.

#### Parameters

- `string listTakenFrom`: The name of the first list to exclude.
- `string listTakenTo`: The name of the second list to exclude.
- `json inputFile`: The JSON object to read.

#### Returns

- `string`: The name of the last list that is not one of the excluded lists.

#### Description

1. **Parse JSON Object**: Examines the JSON object for the lists.
2. **Find Last List**: Searches for the first list in the JSON object that is not excluded by the given names.
3. **Return Result**: Returns the name of this last list.

---

### `void takeOutTransaction(list<list<Transaction>>& listRemovingFrom, list<Transaction>& listAddedTo, int idTaken, string tableIdTaken)`

Removes a specific transaction from a list of transaction groups and adds it to another list.

#### Parameters

- `list<list<Transaction>>& listRemovingFrom`: The list of transaction groups to remove from.
- `list<Transaction>& listAddedTo`: The list to add the removed transaction to.
- `int idTaken`: The ID of the transaction to remove.
- `string tableIdTaken`: The table ID of the transaction to remove.

#### Description

1. **Find Transaction**: Searches for the transaction with the specified ID and table ID.
2. **Remove and Add**: Moves the found transaction from `listRemovingFrom` to `listAddedTo`.

---

### `void takeOutTransaction(list<Transaction>& listRemovingFrom, list<Transaction>& listAdded

To, int idTaken, string tableIdTaken)`

Removes a specific transaction from a list and adds it to another list.

#### Parameters

- `list<Transaction>& listRemovingFrom`: The list to remove the transaction from.
- `list<Transaction>& listAddedTo`: The list to add the removed transaction to.
- `int idTaken`: The ID of the transaction to remove.
- `string tableIdTaken`: The table ID of the transaction to remove.

#### Description

1. **Find Transaction**: Searches for the transaction with the specified ID and table ID.
2. **Remove and Add**: Moves the found transaction from `listRemovingFrom` to `listAddedTo`.

---

### `void reorderListofManuallyMatchedTransactions(list<Transaction>& matchedTrans, list<list<Transaction>> listOfLists)`

Reorders a list of manually matched transactions based on the table ID of the first group in the list.

#### Parameters

- `list<Transaction>& matchedTrans`: The list of matched transactions to reorder.
- `list<list<Transaction>> listOfLists`: The list of transaction groups to base the ordering on.

#### Description

1. **Check Table ID**: Compares the table ID of the first transaction in `matchedTrans` with the table ID of the first group in `listOfLists`.
2. **Reorder**: If they do not match, reorders `matchedTrans` by placing the first transaction at the end of the list.

---

### `void addRelevantTransaction(list<list<Transaction>>& listToAddTo, list<Transaction>& listToRemoveFrom, int idTo, string tableIdTo)`

Adds a relevant transaction to a list of transaction groups and removes it from another list.

#### Parameters

- `list<list<Transaction>>& listToAddTo`: The list of transaction groups to add the transaction to.
- `list<Transaction>& listToRemoveFrom`: The list to remove the transaction from.
- `int idTo`: The ID of the transaction to add.
- `string tableIdTo`: The table ID of the transaction to add.

#### Description

1. **Find Transaction**: Searches for the transaction with the specified ID and table ID in `listToRemoveFrom`.
2. **Add and Remove**: Adds the found transaction to `listToAddTo` and removes it from `listToRemoveFrom`.
3. **Check Table ID**: Ensures the transaction being added is not from the same table ID as the existing transactions in `listToAddTo`.

---

### `void displayJsonInFile(json jsonObject, string nameOfFile)`

Writes a JSON object to a file.

#### Parameters

- `json jsonObject`: The JSON object to write.
- `string nameOfFile`: The name of the file to write to.

#### Description

1. **Open File**: Opens the specified file for writing.
2. **Write JSON**: Writes the JSON object to the file with pretty formatting.
3. **Close File**: Closes the file.

---

### `json repairList(int idTaken, string tableIdTaken, string listTakenFrom, int idTo, string tableIdTo, string listTakenTo, string inputFile)`

Repairs transaction lists by moving transactions between them based on specific criteria and updates the JSON file accordingly.

#### Description

- **Standardization**: Converts `listTakenFrom` and `listTakenTo` to uppercase.
- **Conditions Check**: Determines if `listTakenFrom` and `listTakenTo` contain "UNMATCHED" text.
- **Transaction Adjustment**: Depending on the presence of "UNMATCHED" text and whether the lists are the same, adjusts the transactions between the lists.
- **JSON Output**: Generates a JSON object representing the updated lists and writes it to a file.

---

### `json repairListJson(int idTaken, string tableIdTaken, string listTakenFrom, int idTo, string tableIdTo, string listTakenTo, json inputFile)`

Repairs transaction lists using JSON input data and generates a JSON object with the updated lists.

#### Description

- **Standardization**: Converts `listTakenFrom` and `listTakenTo` to uppercase.
- **Conditions Check**: Determines if `listTakenFrom` and `listTakenTo` contain "UNMATCHED" text.
- **Transaction Adjustment**: Depending on the presence of "UNMATCHED" text and whether the lists are the same, adjusts the transactions between the lists.
- **JSON Output**: Creates a JSON object representing the updated lists based on JSON input data.

---

### `manuallyMatch`
This function compares and matches transactions between two lists identified by `id1` and `id2` from different tables (`tableId1` and `tableId2`). It processes the lists based on their standardized names, manages unmatched transactions, and generates a JSON output of the results, including matched, probable, and unmatched transactions. It ensures that transactions from the same file cannot be matched and handles different scenarios where lists might be unmatched.

---

### `manuallyMatchJson`
Similar to `manuallyMatch`, this function performs transaction matching between two lists, but it operates directly with JSON input. It follows a similar process of comparing lists, handling unmatched transactions, and generating a JSON output with matched, probable, and unmatched transactions. This function is tailored for cases where the input data is already in JSON format, avoiding the need for intermediate file handling.