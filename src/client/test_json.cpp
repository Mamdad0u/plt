#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "jsoncpp/json/value.h"

using namespace std;

int main(void) {

    ifstream ifs("rules.json");
    Json::Reader reader;
    Json::Value obj;

    reader.parse(ifs,obj);
    cout << "Character's statistics : \n" << obj["Statistics"]["IS"]["PV"] <<endl;

    return 0;
}