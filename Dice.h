#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
#pragma once

class Dice
{
private:
	string dice_name;
	int side_amount;
	vector<int> sides;
	vector<int>::iterator myItr;

public:
	Dice(int x);
	Dice() {};
	int Dice_roll();
	float average();
	int max();
};