#include "Dice.h"
#include "Character.h"
#include <bits/stdc++.h>
using namespace std;
// DONT FORGET ITS mingw32-make NOT make
// DONT FORGET ITS mingw32-make clean to clean
// https://github.com/nlohmann/json/tree/develop for json support, info, and methods
// https://github.com/foundryvtt/pf2e/tree/v13-dev for Pathfinder jsons
//  git add . '!:!path/to/excluded-file' 

using namespace std;

int main()
{
	Character Axel("character_jsons/Axel.json");
	// Character Test("character_jsons/Test_template.json");

	Axel.display_Character_Info();
	// Test.display_Character_Info();
}