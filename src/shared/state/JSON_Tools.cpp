#include <state/JSON_tools.h>
#include "Character.h"
#include <iostream>
#include <fstream>
//#include <jsoncpp/json/json.h>
//#include <jsoncpp/json/value.h>

#include </usr/local/include/json/json.h> //MacOS
#include </usr/local/include/json/json.h> //MacOS
#include <string>

namespace state {

    void JSON_Configure_Character (Character &rCharacter) {
        std::ifstream ifs("res/JSON_files/statistics.json");
        
        Json::Reader reader;
        Json::Value obj;
        reader.parse(ifs,obj);


        int newPV = obj["Statistics"][rCharacter.GetName()]["PV"].asInt();
        int newATTACK = obj["Statistics"][rCharacter.GetName()]["ATTACK"].asInt();
        int newPOWER = obj["Statistics"][rCharacter.GetName()]["POWER"].asInt();
        int newDEFENSE = obj["Statistics"][rCharacter.GetName()]["DEFENSE"].asInt();
        int newLUCK = obj["Statistics"][rCharacter.GetName()]["LUCK"].asInt();

        rCharacter.SetCharacterStats(LIFE_POINTS, newPV);
        rCharacter.SetCharacterStats(ATTACK, newATTACK);
        rCharacter.SetCharacterStats(POWER, newPOWER);
        rCharacter.SetCharacterStats(DEFENSE, newDEFENSE);
        rCharacter.SetCharacterStats(LUCK, newLUCK);




    }


}

