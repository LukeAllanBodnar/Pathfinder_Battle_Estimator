#include <iostream>
#include "../Weapon.h"
#include <vector>
using namespace std;
#pragma once

class action
{
private:
	int effective_value;
	int move_cost;
    string action_Name;
    vector<string> traits;

public:
	action() {effective_value = 0; move_cost = 0; action_Name = "N/A";};

    virtual int attack_Action(Weapon *attacker_Weapon, int enemy_AC) = 0;

    // This value will repsent the effectiveness of the move given in a number form
    int get_Effective_Value() {return effective_value;};
    void set_Effective_Value(int new_Value) {effective_value = new_Value;};

    // This is done so when we create a list of actions
    string get_Action_Name() {return action_Name;};
    void set_Action_Name(string name) {action_Name = name;};

    // This is to repesents how many actions the move takes
    int get_Move_Cost() {return effective_value;};
    void set_Move_Cost(int x) {effective_value = x;};

    // This is to give traits to move like attack, and subtle etc
    vector<string> get_Traits() {return traits;};
    void set_Traits(vector<string> list_traits) {traits = list_traits;};
};