#include <map>
#include "Weapon.h"
#include "actions/strike.h"
#include "Armor.h"

using namespace std;
#pragma once

class Character
{
private:

	string Character_ancestry;
	string Character_background;
	string Character_class;
	string Character_heritage;
	string Character_name;
	string keyAbility;

	bool Death = false;

	int level;
	int Max_hp;
	int Current_hp;
	int speed;
	// This is an array in order cha, con, dex, int, str, wis
	map<std::string, int> mapLevelledBoosts;

	/*
	This is a each postion in the vector represents for proficiencies
	This will hold the level of proficiency not the total bonus
	0 - acrobatics
	1 - advanced weapons
	2 - arcana
	3 - athletics
	4 - castingArcane
	5 - castingDivine
	6 - castingOccult
	7 - castingPrimal
	8 - classDC
	9 - crafting
	10 - deception
	11 - diplomacy
	12 - fortitude
	13 - heavy
	14 - intimidation
	15 - light
	16 - martial
	17 - medicine
	18 - medium
	19 - nature
	20 - occultism
	21 - perception
	22 - performance
	23 - reflex
	24 - religion
	25 - simple
	26 - society
	27 - stealth
	28 - survival
	29 - thievery
	30 - unarmed
	31 - unarmored
	32 - will
	*/
	map<string, int> proficiency;

	/* This is each postion in the vector represents for skill proficiencies this will hold the total bonus
	0 - acrobatics
	1 - arcana
	2 - athletics
	3 - crafting
	4 - deception
	5 - diplomacy
	6 - intimidation
	7 - medicine
	8 - nature
	9 - occultism
	10 - performance
	11 - reflex
	12 - religion
	13 - simple
	14 - society
	15 - stealth
	16 - survival
	17 - thievery
	*/
	map<string, int> proficiency_skills;

	// The reason why it is own thing is because there are certian effects taht targets saves verues saving throughs so it will be beeter to put it here
	map<string, int> proficiency_saves;

	// The reason why it is own thing is because there are certian effects taht targets saves verues saving throughs so it will be beeter to put it here
	map<string, int> proficiency_equipment;

	// There a few maps I need to iterate through so I made this
	map<string, int>::iterator myItr;


	// This is to help map stats like cha, str, wis, ect to the write proficiency
	// proficiency_Converstion_Table == pCT
	map<string, string> pCT;

	// Gonna make the list of actions a person cant take
	map<string, action*> character_Actions;

	// List of all the weapons the chracter has
	vector<Armor> Character_Armor;
	vector<Weapon> Character_weapons;
	Weapon* equipped_Weapon;
	Armor* equipped_Armor;

	void load_Character_Info(const json& Data);
	void initialize_Actions();
	void initialize_Character();
	void initialize_Converstion_Table();
	void initialize_Proficiencies();
	void set_Attributes(const json& Data);

public:

	Weapon* get_equipped_Weapon() {return Character::equipped_Weapon;} ;
	string get_Charater_Name() {return Character::Character_name;};
	void display_Character_Info();

	int get_armor_AC() {return equipped_Armor->get_AC();};
	void damage_Taken(int damage);
	bool is_Dead() {return Death;};

	// Here is the list of actions a person can take
	void character_Strike(Character* enemy);

	Character(string Json_name);
	~Character() {
		delete equipped_Weapon;
		delete equipped_Armor;
	}

};