#include "weapon.h"

weapon::weapon( string des , int in_damage , int in_durability ) : Item(description)
{
    weapon_damage = in_damage;
    weapon_durability = in_durability;
    weapon_level = 1;
    description =des + " D " + to_string(in_damage) + "Dur " + to_string(in_durability);
}

/*
weapon::weapon( int in_damage , int in_durability , int in_level ) : Item(description)
{
    weapon_damage = in_damage;
    weapon_durability = in_durability;
    weapon_level = in_level;
}
*/

weapon weapon::operator ++()
{
    this -> weapon_damage += 50;
    this -> weapon_durability +=50;
}

int weapon::getWeaponDamage()
{
    return weapon_damage;
}

int weapon::getWeaponDurability()
{
    return weapon_durability;
}

void weapon::setWeaponDamage(int in_damage)
{
    weapon_damage = in_damage;
}

void weapon::setWeaponDurablilty(int in_durability)
{
    weapon_durability = in_durability;
}

weapon weapon::operator --()
{
    if(weapon_durability >= 5)
        weapon_durability -=5;
    else{
        weapon_damage = 0;
    }
}

string weapon::getDescription()
{
    string temp = "";
    temp += weapon_durability + "+" + weapon_damage;
    return temp;
}
