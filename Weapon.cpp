#include "Weapon.h"

using json = nlohmann::json;
using namespace nlohmann::literals;
using namespace std;

Weapon::Weapon(const json& Data)
{
	json weapon_Data = json::parse(Data.dump(2));
	Weapon::Damage_die.clear();

	Weapon::Attack = weapon_Data["attack"];
	Weapon::DamageType = weapon_Data["damageType"];
	Weapon::Display = weapon_Data["display"];
	Weapon::Name = weapon_Data["name"];
	Weapon::Potency_level = weapon_Data["pot"];
	Weapon::Striking_level = weapon_Data["str"];
	Weapon::WeaponType = weapon_Data["prof"];
	Weapon::damageBonus = weapon_Data["damageBonus"];

	string s = weapon_Data["die"].template get<std::string>();
	s = s.erase(0, 1);

	Weapon::Damage_die = { Dice(stoi(s))};
	if (Weapon::Striking_level.compare("striking"))
	{
		Weapon::Damage_die = { Dice(stoi(s)), Dice(stoi(s)) };
	}
	if (Weapon::Striking_level.compare("greaterStriking"))
	{
		Weapon::Damage_die = { Dice(stoi(s)), Dice(stoi(s)), Dice(stoi(s)) };
	}
	if (Weapon::Striking_level.compare("majorStriking"))
	{
		Weapon::Damage_die = { Dice(stoi(s)), Dice(stoi(s)), Dice(stoi(s)) , Dice(stoi(s))};
	}

	// Since its a json I need to convert it to a string to keep track of length and stuff
	string List_of_runes = weapon_Data["runes"].dump();
	string rune_Name;
	json j = weapon_Data["runes"];

	Weapon::Runes.clear();
	while (List_of_runes.length() > 4)
	{
	    rune_Name = j.begin()->dump();
		Weapon::Runes.push_back(rune_Name);
		j.erase(j.begin());
		List_of_runes = j.dump();
	}

	string Json_name = "equipment/"+ Weapon::Name + ".json";
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
	json weapon_info;
	f >> weapon_info;

	// Since its a json I need to convert it to a string to keep track of length and stuff
	json k = json::parse(weapon_info["system"].dump());
	json v = json::parse(k["traits"].dump());
	string List_of_traits = v["value"].dump();
	string trait_Name;
	json p = v["value"];

	Weapon::traits.clear();
	while (List_of_traits.length() > 4)
	{
	    trait_Name = p.begin()->dump();
		Weapon::traits.push_back(trait_Name);
		p.erase(p.begin());
		List_of_traits = p.dump();
	}

	json first_parse_data = json::parse(weapon_info.dump(2));
	json equipment_Data = first_parse_data["system"];

	Weapon::weaponGroup = equipment_Data["group"];

	if (!equipment_Data["range"].is_null())
	{
		Weapon::range = equipment_Data["range"];
	}

	string m = equipment_Data["reload"].dump();
	if (m.length() > 5)
	{
		json z = json::parse(equipment_Data["reload"].dump());
		if (!(z["value"].is_null()))
		{
			string t = z["value"].dump();
			Weapon::reload = t.at(0);
		}

	}

}

int Weapon::roll_Damage()
{
	int total = 0;
	for (vector<Dice>::iterator myItr = Weapon::Damage_die.begin(); myItr !=Weapon::Damage_die.end(); ++myItr)
	{
		total = total + myItr->Dice_roll();
	}

	total += Weapon::damageBonus;

	return total;
}

int Weapon::roll_Attack()
{
	Dice roll(20);
	return Attack + roll.Dice::Dice_roll();
}

void Weapon::display_Weapon()
{
	cout << Weapon::Display << endl;
	cout << "It is a " << Weapon::WeaponType << " weapon with " << Weapon::Striking_level << endl;
	cout << "This weapon has a +" << Potency_level << " with a total of a " << Weapon::Attack << " to attack" << " to hit that does " + Weapon::DamageType << " D" << Weapon::Damage_die.at(0).max() << endl;

	vector<string>::iterator myItr;

	for (myItr = Weapon::traits.begin(); myItr != Weapon::traits.end(); ++myItr)
	{
		cout << *myItr << "   ";
	}
	cout << endl;

	for (myItr = Weapon::Runes.begin(); myItr != Weapon::Runes.end(); ++myItr)
	{
		cout << *myItr << "   ";
	}
	cout << endl;
}

