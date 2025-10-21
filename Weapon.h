#include "Dice.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include "json\single_include\nlohmann\json.hpp"
using namespace std;
using json = nlohmann::json;
#pragma once

class Weapon
{
private:

	vector<Dice> Damage_die;
	string DamageType;
	string Display;
	string Name;
	string Striking_level;
	string WeaponType;
	vector<string> Runes;
	int Attack;
	int damageBonus;
	int Potency_level;

	int range;
	char reload;
	string weaponGroup;
	vector<string> traits;

public:

	Weapon(const json& Data);
	Weapon() {};

	int roll_Attack();
	int get_Attack() {return Attack;};
	int roll_Damage();
	void display_Weapon();

	~Weapon() {

	}
};