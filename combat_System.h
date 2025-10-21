#include <iostream>
#include <vector>
#include "Dice.h"
using namespace std;
#pragma once

class combat_System
{
private:
    Dice x;
public:
    combat_System() {x = Dice(20);};

    int contested_Check(int modifier, int DC);

};