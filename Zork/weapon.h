#include "item.h"
#include <string>
#ifndef WEAPON_H
#define WEAPON_H


class weapon : public Item
{

private:
    int weapon_damage;
    int weapon_durability;
    int weapon_level;
public:
    weapon(string des ,int in_damage, int in_durability );
    weapon( int in_damage, int in_durability , int in_level);
    int getWeaponDamage();
    int getWeaponLevel();
    int getWeaponDurability();
    void setWeaponDamage( int in_damage);
    void setWeaponLevel();
    void setWeaponDurablilty( int in_durability);
    string getDescription();
    weapon operator++();
    weapon operator--();

};
#endif // WEAPON_H