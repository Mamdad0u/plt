#include "Character.h"
#include <fstream>
#include <iostream>
#include <state/JSON_tools.h>
#include <string>

#include "json/json.h"

using namespace state;

JSON_tools::JSON_tools() {

  // open file
  std::ifstream ifs;
  ifs.open("res/JSON_files/test.json");
  if (!ifs.is_open()) {
    std::cout << "can't open "
              << "res/JSON_files/test.json" << std::endl;
    exit(1);
  }

  // parse the json file
  Json::CharReaderBuilder builder;
  Json::Value root;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    std::cout << errs << std::endl;
    exit(1);
  }

  std::cout << "DEBUG " << root["IS"].asString() << std::endl;
}

void JSON_tools::JSON_Configure_Character(Character rCharacter) {
  std::ifstream ifs("res/JSON_files/statistics.json");

  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);

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
