#include "Armor.h"

using json = nlohmann::json;
using namespace nlohmann::literals;
using namespace std;

Armor::Armor(const json& Data)
{
	json armor_Data = json::parse(Data.dump(2));

	Armor::Display = armor_Data["display"];
	Armor::Name = armor_Data["name"];
	Armor::Potency_level = armor_Data["pot"];
	Armor::Resilient_level = armor_Data["res"];
	Armor::ArmorType = armor_Data["prof"];

	// Since its a json I need to convert it to a string to keep track of length and stuff
	string List_of_runes = armor_Data["runes"].dump();
	string rune_Name;
	json j = armor_Data["runes"];

	Armor::Runes.clear();
	while (List_of_runes.length() > 4)
	{
	    rune_Name = j.begin()->dump();
		Armor::Runes.push_back(rune_Name);
		j.erase(j.begin());
		List_of_runes = j.dump();
	}

	string Json_name = "equipment/"+ Armor::Name + ".json";
	// I need to convert the string to the name of the json file
	for_each(Json_name.begin(), Json_name.end(), [](char& c)
	{
        if (c == ' ')
		{
			c = '-';
		}
		c = tolower(c);
    });

	std::stringstream ss;
	std::ifstream f(Json_name);
	json armor_info;
	f >> armor_info;

	// Since its a json I need to convert it to a string to keep track of length and stuff
	json k = json::parse(armor_info["system"].dump());
	json v = json::parse(k["traits"].dump());
	string List_of_traits = v["value"].dump();
	string trait_Name;
	json p = v["value"];

	Armor::traits.clear();
	while (List_of_traits.length() > 4)
	{
	    trait_Name = p.begin()->dump();
		Armor::traits.push_back(trait_Name);
		p.erase(p.begin());
		List_of_traits = p.dump();
	}

	json first_parse_data = json::parse(armor_info.dump(2));
	json equipment_Data = first_parse_data["system"];

	Armor::acBonus = equipment_Data["acBonus"];
	Armor::armorGroup = equipment_Data["group"];
	Armor::strRequirements = equipment_Data["strength"];
	Armor::dexCap = equipment_Data["dexCap"];
	Armor::speedPenalty = equipment_Data["speedPenalty"];
}

void Armor::construct_Ac(int dex_Modifier, map<string, int> proficiency_equipment)
{
	int dexBonus = dex_Modifier;
	if (dex_Modifier > Armor::dexCap)
	{
		dexBonus = Armor::dexCap;
	}
	Armor::acTotal = dexBonus + proficiency_equipment.at(Armor::ArmorType) + Armor::acBonus + Armor::Potency_level + 10;
}

void Armor::display_Armor()
{
	cout << Armor::Display << endl;
	cout << "It is a " << Armor::Name;
	if (!Armor::Runes.empty())
	{
		cout << "with these propety runes ";
		vector<string>::iterator myItr;
		for (myItr = Armor::Runes.begin(); myItr != Armor::Runes.end(); ++myItr)
		{
			cout << *myItr << "   ";
		}
		cout << endl;
	}

	if (!Armor::traits.empty())
	{
		cout << "with these traits ";
		vector<string>::iterator myItr;
		for (myItr = Armor::traits.begin(); myItr != Armor::traits.end(); ++myItr)
		{
			cout << *myItr << "   ";
		}
		cout << endl;
	}

	cout << ". It has + " <<  Armor::Potency_level << " to Ac";
	if (Armor::Resilient_level.length() > 3)
	{
	cout << " with a " << Armor::Resilient_level << " rune" << endl;
	}

	cout << "with an acTotal of " << Armor::acTotal << endl;
}