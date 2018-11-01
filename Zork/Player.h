#include "Character.h"
#include <vector>
#include <item.h>

#ifndef PLAYER_H
#define PLAYER_H


class Player : public Character
{
private:
    vector<Item> inventory;

public:
    Player(int health);

    void addItemToInvetory(Item & item);
    void removeItemFromInventory(int pos);
    vector<Item>& getInventory();
    void onDeath();
};

#endif // PLAYER_H
