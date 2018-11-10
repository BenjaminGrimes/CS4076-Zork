#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <string>

using std::string;

#define MAX_HEALTH 100
#define MIN_HEALTH 0

class Enemy : public Character
{
private:
    string name;

public:
    Enemy(int health);

    void onDeath();

    Enemy &operator++(); // Prefix increment
    Enemy operator++(int); // Postfix increment
    Enemy &operator--(); // Prefix decrement
    Enemy operator--(int); // Postfix decrement
};

#endif // ENEMY_H
