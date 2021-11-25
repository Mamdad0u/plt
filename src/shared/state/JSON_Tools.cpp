#include <state/JSON_Tools.h>
#include "Character.h"
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <string>

namespace state {

    void JSON_Configure_Character (Character &rCharacter) {
        std::ifstream ifs("res/JSON_files/statistics.json");
        
        Json::Reader reader;
        Json::Value obj;
        reader.parse(ifs,obj);


        int newPV = obj["Statistics"][rCharacter.mCharacterName]["PV"].asInt();
        int newATTACK = obj["Statistics"][rCharacter.mCharacterName]["ATTACK"].asInt();
        int newPOWER = obj["Statistics"][rCharacter.mCharacterName]["POWER"].asInt();
        int newDEFENSE = obj["Statistics"][rCharacter.mCharacterName]["DEFENSE"].asInt();
        int newLUCK = obj["Statistics"][rCharacter.mCharacterName]["LUCK"].asInt();

        rCharacter.SetCharacterStats(LIFE_POINTS, newPV);
        rCharacter.SetCharacterStats(ATTACK, newATTACK);
        rCharacter.SetCharacterStats(POWER, newPOWER);
        rCharacter.SetCharacterStats(DEFENSE, newDEFENSE);
        rCharacter.SetCharacterStats(LUCK, newLUCK);




    }


}

