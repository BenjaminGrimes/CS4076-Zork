#include "Character.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy : public Character
{
public:
    Enemy(int health);

    void onDeath();
};

#endif // ENEMY_H
