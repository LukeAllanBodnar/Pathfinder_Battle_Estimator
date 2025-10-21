#include "Dice.h"
#include <iostream>
#include <sstream>

float Dice::average()
{
	float average = (1+Dice::side_amount)/2.0f;

	return average;
}

Dice::max()
{
	return Dice::side_amount;
}

Dice::Dice_roll()
{
	// Define range
	int min = 1;
	int max = Dice::side_amount;

	// Initialize a random number generator
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);

	// Generate random number in the range [min, max]
	int randomValue = distrib(gen);
	return randomValue;
}

Dice::Dice(int x)
	: side_amount{x}
{
	// This is to check for dice rolled in a ttrpg system
	switch (x)
	{
	case 4:
		break;
	case 6:
		break;
	case 8:
		break;
	case 10:
		break;
	case 12:
		break;
	case 20:
		break;
	default:
		cout << "error: incorrect value for dice" << endl;
		return;
	}

	// names the dice by how many sides it has
	std::stringstream sstm;
	sstm << "D" << x;
	Dice::dice_name = sstm.str();

	Dice::sides.resize(x);
	int i = 0;

	for (Dice::myItr = sides.begin(); Dice::myItr != sides.end(); ++Dice::myItr) {
		++i;
		*myItr = i;
	}
}