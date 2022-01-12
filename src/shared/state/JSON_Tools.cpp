#include "JSON_tools.h"
#include "Character.h"
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

//#include </usr/local/include/json/json.h> //MacOS
//#include </usr/local/include/json/json.h> //MacOS
#include <string>

using namespace std;
namespace state {

    typedef struct ActionContainer{
        int damage;
        StatsName stat;
        ActionListCommand type;
        int beneficial;
        int buff;

    }ActionContainer;
    void JSON_tools::JSON_Configure_Character (Character& rCharacter) {
        std::ifstream ifs("res/JSON_files/statistics.json");
        string lAction_Name[] = {"ACTION_1", "ACTION_2", "ACTION_3", "ACTION_4"};
        string lAction_Type[] = {"ATTACK_1", "ATTACK_2", "SPELL_1", "SPELL_2"};
        Json::Reader reader;
        Json::Value obj;
        ActionContainer lActionList[4];
        reader.parse(ifs,obj);


        int newPV = obj["Statistics"][rCharacter.GetName()]["PV"].asInt();
        int newATTACK = obj["Statistics"][rCharacter.GetName()]["ATTACK"].asInt();
        int newPOWER = obj["Statistics"][rCharacter.GetName()]["POWER"].asInt();
        int newDEFENSE = obj["Statistics"][rCharacter.GetName()]["DEFENSE"].asInt();
        int newLUCK = obj["Statistics"][rCharacter.GetName()]["LUCK"].asInt();
        int capacityNumber = obj["Statistics"][rCharacter.GetName()]["CAPACITY_NUMBER"].asInt();

        for(int lIndex_Action=0;lIndex_Action<capacityNumber; lIndex_Action++){
        
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
            }
                lActionList[lIndex_Action].type =  (ActionListCommand)obj["Statistics"][rCharacter.GetName()][lAction_Name[lIndex_Action]]["TYPE"].asInt();
                
                switch (lActionList[lIndex_Action].type)
                {
                case ATTACK_1:
                    rCharacter.SetCharacterAction(ATTACK_1, lActionList[lIndex_Action].damage, lActionList[lIndex_Action].stat, lActionList[lIndex_Action].buff, (BuffType)lActionList[lIndex_Action].beneficial);
                    break;

                case ATTACK_2:
                    rCharacter.SetCharacterAction(ATTACK_2, lActionList[lIndex_Action].damage, lActionList[lIndex_Action].stat, lActionList[lIndex_Action].buff, (BuffType)lActionList[lIndex_Action].beneficial);
                    break;

                case SPELL_1:
                    rCharacter.SetCharacterAction(SPELL_1, lActionList[lIndex_Action].damage, lActionList[lIndex_Action].stat, lActionList[lIndex_Action].buff, (BuffType)lActionList[lIndex_Action].beneficial);
                    break;

                case SPELL_2:
                    rCharacter.SetCharacterAction(SPELL_2, lActionList[lIndex_Action].damage, lActionList[lIndex_Action].stat, lActionList[lIndex_Action].buff, (BuffType)lActionList[lIndex_Action].beneficial);
                    break;
                }
            


        }
        

        
        rCharacter.SetCharacterStats(LIFE_POINTS, newPV);
        rCharacter.SetCharacterStats(ATTACK, newATTACK);
        rCharacter.SetCharacterStats(POWER, newPOWER);
        rCharacter.SetCharacterStats(DEFENSE, newDEFENSE);
        rCharacter.SetCharacterStats(LUCK, newLUCK);




    }


}
