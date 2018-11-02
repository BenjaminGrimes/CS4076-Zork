#include "Character.h"
#include <vector>
#include <item.h>
#include <QString>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H


class Player : public Character
{
private:
    string name;
    int age;
    string sex;
    vector<Item> inventory;

public:
    Player(int health);

    void addItemToInvetory(Item & item);
    void removeItemFromInventory(int pos);
    void setPlayerInfo(QString name, int age, QString sex);
    vector<Item>& getInventory();
    void onDeath();
};

#endif // PLAYER_H
