#include "Character.h"
using namespace std;
using json = nlohmann::json;
using namespace nlohmann::literals;

Character::Character(string Json_name)
{
	initialize_Character();
	std::stringstream ss;
	std::ifstream f(Json_name);
	json j;
	f >> j;

	// json is so big that I have to split it up in smaller jsons for the functions to work
	json first_parse_data = json::parse(j.dump(2));
	json second_parse_data = first_parse_data["build"];

	// List of jsons I want for the character
	json proficiency_data = second_parse_data["proficiencies"];
	json weapon_data = second_parse_data["weapons"];
	json armor_data = second_parse_data["armor"];
	json attributes_data = second_parse_data["attributes"];

	// Loads name, race, background, ect for chracter info
	Character::load_Character_Info(second_parse_data);

	// sets speed and hp of character
	Character::set_Attributes(attributes_data);

	// set the map between ability scores and proficiencies
	Character::initialize_Converstion_Table();

	// Have to delete the first entry becuase first line is how those stats became to be not the stats itself
	json mapLevelledBoosts_data = second_parse_data["abilities"];
	mapLevelledBoosts_data.erase(mapLevelledBoosts_data.begin());

	// assigns the atributes of the game like STR, DEX, ect to a map {the whole score}
	json::iterator it = mapLevelledBoosts_data.begin();
	for (myItr = Character::mapLevelledBoosts.begin(); myItr != Character::mapLevelledBoosts.end(); ++myItr)
	{
		int k = *it;
		myItr->second = (k/2) - 5;
		++it;
	}

	// assigns the proficiency of the game like acrobatics, medium armor, ect to a map {only part of it}
	it = proficiency_data.begin();
	for (myItr = Character::proficiency.begin(); myItr != Character::proficiency.end(); ++myItr)
	{
		myItr->second = *it;
		++it;
	}

	Character::initialize_Proficiencies();
	Character::Current_hp = Character::Max_hp;

	Character::Character_Armor.resize(armor_data.size());
	for (int i = 0; i < Character::Character_Armor.size(); ++i)
	{
		Character::Character_Armor.at(i) = Armor(armor_data.at(i));
		Character::Character_Armor.at(i).construct_Ac(Character::mapLevelledBoosts.at("dex"), Character::proficiency_equipment);
	}

	if (Character::Character_Armor.size() != 0)
	{
		equipped_Armor = &Character::Character_Armor.at(0);
	}

	Character::Character_weapons.resize(weapon_data.size());
	for (int i = 0; i < Character::Character_weapons.size(); ++i)
	{
		Character::Character_weapons.at(i) = Weapon(weapon_data.at(i));
	}

	if (Character::Character_weapons.size() != 0)
	{
		equipped_Weapon = &Character::Character_weapons.at(0);
	}
}

void Character::display_Character_Info()
{

	cout << "Character loaded" << endl;
	cout << "Name: " << Character::Character_name << " | Race: " << Character::Character_ancestry << " | Subrace: " << Character::Character_heritage << endl;
	cout << "Background: " << Character::Character_background << " | Class: " << Character::Character_class << " | Level : " << Character::level << endl;
	cout << "HP: " << Character::Max_hp << endl;
	cout << "Modifiers:" << endl;

	for (myItr = Character::mapLevelledBoosts.begin(); myItr != Character::mapLevelledBoosts.end(); ++myItr)
	{
		cout << myItr->first << ": " << myItr->second << endl;
	}

	cout << "Skills:" << endl;
	for (myItr = Character::proficiency_skills.begin(); myItr != Character::proficiency_skills.end(); ++myItr)
	{
		cout << myItr->first << ": " << myItr->second << endl;
	}

	Character::equipped_Armor->display_Armor();
	Character::equipped_Weapon->display_Weapon();
}


void Character::set_Attributes(const json& Data)
{
	json attributes_Data = json::parse(Data.dump(2));
	int intial_hp = attributes_Data["ancestryhp"];
	int intial_bonus_hp = attributes_Data["bonushp"];
	int classhp = attributes_Data["classhp"];
	int base_speed = attributes_Data["speed"];
	int speedBonus = attributes_Data["speedBonus"];
	int bonushpPerLevel = attributes_Data["bonushpPerLevel"];

	Character::Max_hp = ((classhp + bonushpPerLevel) * Character::level) + intial_bonus_hp + intial_hp;
	Character::speed = base_speed + speedBonus;
}

void Character::load_Character_Info(const json& Data)
{
	json character_info_Data = json::parse(Data.dump(2));

	Character::level = character_info_Data["level"];
	Character::Character_ancestry = character_info_Data["ancestry"];
	Character::Character_background = character_info_Data["background"];
	Character::Character_class = character_info_Data["class"];
	Character::Character_heritage = character_info_Data["heritage"];
	Character::Character_name = character_info_Data["name"];
    Character::keyAbility = character_info_Data["keyability"];
}

void Character::initialize_Proficiencies()
{
	for (myItr = Character::proficiency_skills.begin(); myItr != Character::proficiency_skills.end(); ++myItr)
	{
		myItr->second = Character::level + Character::proficiency[myItr->first] + Character::mapLevelledBoosts[Character::pCT[myItr->first]];
	}

	for (myItr = Character::proficiency_saves.begin(); myItr != Character::proficiency_saves.end(); ++myItr)
	{
		myItr->second = Character::level + Character::proficiency[myItr->first] + Character::mapLevelledBoosts[Character::pCT[myItr->first]];
	}

	for (myItr = Character::proficiency_equipment.begin(); myItr != Character::proficiency_equipment.end(); ++myItr)
	{
		myItr->second = Character::level + Character::proficiency[myItr->first];
	}
}

void Character::damage_Taken(int damage)
{
	cout << Character::Character_name <<  "Took " << damage << " Of damage" << endl;

	Character::Current_hp =- damage;

	if(Character::Current_hp > 0)
	{
		Character::Death = true;
	}
}

void Character::initialize_Converstion_Table()
{
	Character::pCT = {
		{"acrobatics" , "dex"},
		{"arcana", "int"},
		{"athletics", "str"},
		{"classDC", Character::keyAbility},
		{"crafting", "int"},
		{"deception", "cha"},
		{"diplomacy", "cha"},
		{"fortitude", "con"},
		{"intimidation", "cha"},
		{"medicine", "wis"},
		{"nature", "wis"},
		{"occultism", "int"},
		{"perception", "wis"},
		{"performance", "cha"},
		{"reflex", "dex"},
		{"religion", "wis"},
		{"society", "int"},
		{"stealth", "dex"},
		{"survival", "wis"},
		{"thievery", "dex"},
		{"will", "wis"}
	};
}

void Character::initialize_Character()
{
	Character::character_Actions = {
		{"Strike", new strike()}
	};

	Character::proficiency_equipment = {
		{"advanced", 0},
		{"heavy", 0},
		{"light", 0},
		{"martial", 0},
		{"medium", 0},
		{"simple", 0},
		{"unarmed", 0},
		{"unarmored", 0},
	};

	Character::proficiency_saves = {
		{"fortitude", 0},
		{"reflex", 0},
		{"will", 0}
	};

	Character::proficiency_skills = {
		{"acrobatics" , 0},
		{"arcana", 0},
		{"athletics", 0},
		{"crafting", 0},
		{"deception", 0},
		{"diplomacy", 0},
		{"intimidation", 0},
		{"medicine", 0},
		{"nature", 0},
		{"occultism", 0},
		{"perception", 0},
		{"performance", 0},
		{"religion", 0},
		{"society", 0},
		{"stealth", 0},
		{"survival", 0},
		{"thievery", 0},
	};

	Character::proficiency = {
		{"acrobatics" , 0},
		{"advanced", 0},
		{"arcana", 0},
		{"athletics", 0},
		{"castingArcane", 0},
		{"castingDivine", 0},
		{"castingOccult", 0},
		{"castingPrimal", 0},
		{"classDC", 0},
		{"crafting", 0},
		{"deception", 0},
		{"diplomacy", 0},
		{"fortitude", 0},
		{"heavy", 0},
		{"intimidation", 0},
		{"light", 0},
		{"martial", 0},
		{"medicine", 0},
		{"medium", 0},
		{"nature", 0},
		{"occultism", 0},
		{"perception", 0},
		{"performance", 0},
		{"reflex", 0},
		{"religion", 0},
		{"simple", 0},
		{"society", 0 },
		{"stealth", 0 },
		{"survival", 0 },
		{"thievery", 0},
		{"unarmed", 0},
		{"unarmored", 0},
		{"will", 0}
	};

	Character::mapLevelledBoosts = {
		{"cha", 10},
		{"con", 10},
		{"dex", 10},
		{"int", 10},
		{"str", 10},
		{"wis", 10}
	};
}

// I am going to put all character options here until I can find a better way of listing them
void Character::character_Strike(Character* enemy)
{
	int damage = 0;

	cout << Character::character_Actions.at("Strike")->get_Action_Name() << endl;

	damage = Character::character_Actions.at("Strike")->attack_Action(this->get_equipped_Weapon(), enemy->get_armor_AC());

	enemy->damage_Taken(damage);
}