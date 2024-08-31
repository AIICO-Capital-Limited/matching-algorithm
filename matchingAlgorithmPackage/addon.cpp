#include "Functions.h"
#include <node.h>

using namespace v8;

void manuallyMatchForJson(const FunctionCallbackInfo<Value>& args);
void matchTransactionsForJson(const FunctionCallbackInfo<Value>& args);
void repairForJson(const FunctionCallbackInfo<Value>& args);
void setPercentToMatchForJson(const FunctionCallbackInfo<Value>& args);
void setPercentToProbMatchForJson(const FunctionCallbackInfo<Value>& args);


void matchTransactionsForJson(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 5 || 
        !args[0]->IsString() || 
        !args[1]->IsString() || 
        !args[2]->IsString() || 
        !args[3]->IsString() || 
        !args[4]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
        return;
    }

    // Convert JavaScript objects to JSON
    Local<Object> firstListString = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
    Local<Object> secondListString = args[1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
    
    String::Utf8Value nameForMatch(isolate, args[2]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    String::Utf8Value nameForProb(isolate, args[3]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    String::Utf8Value nameForUnmat(isolate, args[4]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    
    json firstList = json::parse(*String::Utf8Value(isolate, firstListString->ToString(isolate->GetCurrentContext()).ToLocalChecked()));
    json secondList = json::parse(*String::Utf8Value(isolate, secondListString->ToString(isolate->GetCurrentContext()).ToLocalChecked()));

    // Call the C++ function
    json result = getMatchedProbableMatchAndUnmatchedFromJsonLists(firstList, secondList, *nameForMatch, *nameForProb, *nameForUnmat);

    // Convert JSON result to JavaScript object
    std::string resultStr = result.dump();
    Local<String> resultJs = String::NewFromUtf8(isolate, resultStr.c_str(), NewStringType::kNormal).ToLocalChecked();
    args.GetReturnValue().Set(resultJs);
}

void repairForJson(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 7 || 
        !args[0]->IsNumber() || 
        !args[1]->IsString() || 
        !args[2]->IsString() || 
        !args[3]->IsNumber() || 
        !args[4]->IsString() ||
        !args[5]->IsString() ||
        !args[6]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
        return;
    }

    // Convert JavaScript output to C++ input
    int idTaken = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();
    String::Utf8Value tableIdTaken(isolate, args[1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    String::Utf8Value listTakenFrom(isolate, args[2]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    int idTo = args[3]->Int32Value(isolate->GetCurrentContext()).FromJust();
    String::Utf8Value tableIdTo(isolate, args[4]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    String::Utf8Value listTakenTo(isolate, args[5]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    Local<Object> objectToAdjustString = args[6]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
    
    json objectToAdjust = json::parse(*String::Utf8Value(isolate, objectToAdjustString->ToString(isolate->GetCurrentContext()).ToLocalChecked()));

    // Call the C++ function
    json result = repairListJson(idTaken, *tableIdTaken, *listTakenFrom, idTo, *tableIdTo, *listTakenTo, objectToAdjust);

    // Convert JSON result to JavaScript object
    std::string resultStr = result.dump();
    Local<String> resultJs = String::NewFromUtf8(isolate, resultStr.c_str(), NewStringType::kNormal).ToLocalChecked();
    args.GetReturnValue().Set(resultJs);
}

void manuallyMatchForJson(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    
    if (args.Length() != 7 || 
        !args[0]->IsNumber() || 
        !args[1]->IsString() || 
        !args[2]->IsString() || 
        !args[3]->IsNumber() || 
        !args[4]->IsString() ||
        !args[5]->IsString() ||
        !args[6]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
        return;
    }

    // Convert JavaScript output to C++ input
    int idTaken = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();
    String::Utf8Value tableIdTaken(isolate, args[1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    String::Utf8Value listTakenFrom(isolate, args[2]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    int idTo = args[3]->Int32Value(isolate->GetCurrentContext()).FromJust();
    String::Utf8Value tableIdTo(isolate, args[4]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
    String::Utf8Value listTakenTo(isolate, args[5]->ToString(isolate->GetCurrentContext()).ToLocalChecked());

    Local<Object> objectToAdjustString = args[6]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
    
    json objectToAdjust = json::parse(*String::Utf8Value(isolate, objectToAdjustString->ToString(isolate->GetCurrentContext()).ToLocalChecked()));

    // Call the C++ function
    json result = manuallyMatchJson(idTaken, *tableIdTaken, *listTakenFrom, idTo, *tableIdTo, *listTakenTo, objectToAdjust);

    // Convert JSON result to JavaScript object
    std::string resultStr = result.dump();
    Local<String> resultJs = String::NewFromUtf8(isolate, resultStr.c_str(), NewStringType::kNormal).ToLocalChecked();
    args.GetReturnValue().Set(resultJs);
}

void setPercentToMatchForJson(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();

    if(args.Length() != 1 || !args[0]->IsNumber()){
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
        return;
    }

    int percentMatch = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();

    setPercentToMatch(percentMatch);
}

void setPercentToProbMatchForJson(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();

    if(args.Length() != 1 || !args[0]->IsNumber()){
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
        return;
    }

    int percentProbMatch = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();

    setPercentToProbMatch(percentProbMatch);
}

void setDaysToMatchForJson(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();

    if(args.Length() != 1 || !args[0]->IsNumber()){
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
        return;
    }

    int daysToMatch = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();

    setDaysToMatch(daysToMatch);
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "setPercentToMatch", setPercentToMatchForJson);
    NODE_SET_METHOD(exports, "matchTransactions", matchTransactionsForJson);
    NODE_SET_METHOD(exports, "repairMatches", repairForJson);
    NODE_SET_METHOD(exports, "manuallyMatch", manuallyMatchForJson);
    NODE_SET_METHOD(exports, "setPercentToProbMatch", setPercentToProbMatchForJson);
    NODE_SET_METHOD(exports, "setDaysToMatch", setDaysToMatchForJson);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)