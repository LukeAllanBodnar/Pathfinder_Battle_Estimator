#include "action.h"
#include "../combat_System.h"
using namespace std;
#pragma once

class strike : public action
{
private:
	combat_System x;

public:
	int attack_Action(Weapon *attacker_Weapon, int enemy_AC) override;
	strike();
};