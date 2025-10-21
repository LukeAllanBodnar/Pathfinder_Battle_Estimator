#include "strike.h"
using namespace std;

strike::strike()
{
    this->set_Action_Name("Strike");
    this->set_Move_Cost(1);
    vector<string> list_traits = {"Attack"};
    this->set_Traits(list_traits);
}

int strike::attack_Action(Weapon *attacker_Weapon, int enemy_AC)
{
    int result = strike::x.contested_Check(attacker_Weapon->get_Attack(), enemy_AC);

    int damage = 0;

    switch(result)
    {
        case 0:
            cout << " That is a critcal miss" << endl;

            break;
        case 1:
            cout << " That is a miss" << endl;

            break;
        case 2:
            cout << " That is a hit" << endl;

            damage = attacker_Weapon->roll_Damage();

            break;
        case 3:
            cout << " That is a critcal hit" << endl;

            damage = 2*(attacker_Weapon->roll_Damage());
        break;
    }
    return damage;
}