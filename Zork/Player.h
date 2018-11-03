#include "Character.h"
#include <vector>
#include <item.h>
#include <QString>
#include <string>

using std::string;

#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HEALTH 100
#define MIN_HEALTH 0

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

    Player &operator++(); // Prefix increment
    Player operator++(int); // Postfix increment
    Player &operator--(); // Prefix decrement
    Player operator--(int); // Postfix decrement
};

#endif // PLAYER_H
