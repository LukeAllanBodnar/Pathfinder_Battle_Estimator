#include "combat_System.h"

using namespace std;

int combat_System::contested_Check(int modifier, int DC)
{
    int roll = combat_System::x.Dice_roll();
    int success = 3;

    if (roll == 1) {success -= 1;}

    if (roll == 20) { success += 1;}

    if (((modifier+roll) < DC))
    {
        success -= 1;

        if (((modifier+roll+10) <= (DC)))
        {
            success -= 1;
        }
    }

    if (((modifier+roll) >= (DC+10))) { success += 1; }

    int result = 0;

    cout << "This is the success number " << success << endl;

    if (success < 2) {result = 0;}
    if (success == 2) {result = 1;}
    if (success == 3) {result = 2;}
    if (3 < success) {result = 3;}

    cout << result << endl;

    cout << "Rolled a " << roll << " On the Dice for a total of " << modifier+roll;

    return result;
}