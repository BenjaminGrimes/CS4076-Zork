#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <vector>
#include <item.h>
#include <QString>
#include <string>
#include <QMessageBox>
#include "weapon.h"

using std::string;

#define MAX_HEALTH 100
#define MIN_HEALTH 0

#define MAX_MAGIC_LEVEL 100
#define MIN_MAGIC_LEVEL 0

class Player : public Character
{
private:
    string name;
    int magic_level;
    int age;
    string sex;
    vector<Item> inventory;
    Item *p_weapon;

public:
    Player(int health);

    void addItemToInvetory(Item & item);
    void removeItemFromInventory(int pos);
    void setPlayerInfo(QString name, int age, QString sex);
    vector<Item>& getInventory();
    string getName();
    int getAge();
    string getSex();
    int getMagicLevel();

    void onDeath();

    Player &operator++(); // Prefix increment
    Player operator++(int); // Postfix increment
    Player &operator--(); // Prefix decrement
    Player operator--(int); // Postfix decrement
};

#endif // PLAYER_H
