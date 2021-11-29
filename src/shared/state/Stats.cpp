#include <state/Stats.h>  // Included from library shared_static
#include "Stats.h"

namespace state {

Stats::Stats() {
    this->mDefense = DEFAULT_STATS_VALUE;
    this->mAttack = DEFAULT_STATS_VALUE;
    this->mLife_points = DEFAULT_STATS_VALUE;
    this->mLuck = DEFAULT_STATS_VALUE;
    this->mMax_life_points = DEFAULT_STATS_VALUE;
    this->mPower = DEFAULT_STATS_VALUE;
}

int Stats::Get_max_life_points() {
    return this->mMax_life_points;
}

void Stats::Set_max_life_points(int rValue) {
    this->mMax_life_points = rValue;
}

int Stats::Get_life_points() {
    return this->mLife_points;
}

void Stats::Set_life_points(int rValue) {
    this->mLife_points = rValue;

    if(mLife_points<0){
        mLife_points = 0;
    }
}

int Stats::Get_attack() {
    return this->mAttack;
}

void Stats::Set_attack(int rValue) {
    this->mAttack = rValue;
}

int Stats::Get_power() {
    return this->mPower;
}

void Stats::Set_power(int rValue) {
    this->mPower = rValue;
}

int Stats::Get_defense() {
    return this->mDefense;
}

void Stats::Set_defense(int rValue) {
    this->mDefense = rValue;
}

int Stats::Get_luck() {
    return this->mLuck;
}

void Stats::Set_luck(int rValue) {
    this->mLuck = rValue;
}

}