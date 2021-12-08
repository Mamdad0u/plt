#include <state/JSON_tools.h>
#include "Character.h"
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <string>

using namespace std;
namespace state {

    typedef struct ActionContainer{
        int damage;
        StatsName stat;
        int beneficial;
        int buff;

    }ActionContainer;
    void JSON_tools::JSON_Configure_Character (Character& rCharacter) {
        std::ifstream ifs("res/JSON_files/statistics.json");
        string lAction_Name[] = {"ACTION_1", "ACTION_2", "ACTION_3", "ACTION_4"};
        Json::Reader reader;
        Json::Value obj;
        ActionContainer lActionList[4];
        reader.parse(ifs,obj);


        int newPV = obj["Statistics"][rCharacter.GetName()]["PV"].asInt();
        int newATTACK = obj["Statistics"][rCharacter.GetName()]["ATTACK"].asInt();
        int newPOWER = obj["Statistics"][rCharacter.GetName()]["POWER"].asInt();
        int newDEFENSE = obj["Statistics"][rCharacter.GetName()]["DEFENSE"].asInt();
        int newLUCK = obj["Statistics"][rCharacter.GetName()]["LUCK"].asInt();

        for(int lIndex_Action=0;lIndex_Action<4; lIndex_Action++){
        
            for(int lStatToGet =0;lStatToGet<4;lStatToGet++){
                switch (lStatToGet)
                {
                case 0:
                    lActionList[lIndex_Action].damage = obj["Statistics"][rCharacter.GetName()][lAction_Name[lIndex_Action]]["DAMAGE"].asInt();
                    break;
                
                case 1:
                    lActionList[lIndex_Action].stat = (StatsName)obj["Statistics"][rCharacter.GetName()][lAction_Name[lIndex_Action]]["STATS"].asInt();
                    break;
                
                case 2:
                    lActionList[lIndex_Action].buff = (StatsName)obj["Statistics"][rCharacter.GetName()][lAction_Name[lIndex_Action]]["BUFF"].asInt();
                    break;

                case 3:
                    lActionList[lIndex_Action].beneficial = (StatsName)obj["Statistics"][rCharacter.GetName()][lAction_Name[lIndex_Action]]["BENEFICIAL"].asInt();
                    break;
                }

                switch (lIndex_Action)
                {
                case 0:
                    rCharacter.SetCharacterAction(ATTACK_1, lActionList[0].damage, lActionList[0].stat, lActionList[0].buff, (BuffType)lActionList[0].beneficial);
                    break;

                case 1:
                    rCharacter.SetCharacterAction(ATTACK_2, lActionList[1].damage, lActionList[1].stat, lActionList[1].buff, (BuffType)lActionList[1].beneficial);
                    break;

                case 2:
                    rCharacter.SetCharacterAction(SPELL_1, lActionList[2].damage, lActionList[2].stat, lActionList[2].buff, (BuffType)lActionList[2].beneficial);
                    break;

                case 3:
                    rCharacter.SetCharacterAction(SPELL_2, lActionList[3].damage, lActionList[3].stat, lActionList[3].buff, (BuffType)lActionList[3].beneficial);
                    break;
                }
            }


        }
        

        
        rCharacter.SetCharacterStats(LIFE_POINTS, newPV);
        rCharacter.SetCharacterStats(ATTACK, newATTACK);
        rCharacter.SetCharacterStats(POWER, newPOWER);
        rCharacter.SetCharacterStats(DEFENSE, newDEFENSE);
        rCharacter.SetCharacterStats(LUCK, newLUCK);




    }


}

