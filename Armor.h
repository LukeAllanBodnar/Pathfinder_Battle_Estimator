#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <istream>
#include <bits/stdc++.h>
#include "json\single_include\nlohmann\json.hpp"
using namespace std;
using json = nlohmann::json;
#pragma once

class Armor
{
private:

	// these value we get from the chracter sheet directly
	string Display;
	string Name;
	string Resilient_level;
	string ArmorType;
	vector<string> Runes;
	int Potency_level;
	int acTotal;

	// These values we get from the local json of the armor of the same name
	string armorGroup;
	int acBonus;
	int bulk;
	int checkPenalty;
	int dexCap;
	int strRequirements;
	signed int speedPenalty;
	vector<string> traits;

public:

	Armor(const json& Data);
	Armor() {};
	void construct_Ac(int dex_Modifier, map<string, int> proficiency_equipment);
	void display_Armor();

	int get_AC() {return acTotal;};

	~Armor() {

	}
};