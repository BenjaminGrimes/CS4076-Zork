#include "Character.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player : public Character
{
private:


public:
    Player(int health);

    void onDeath();
};

#endif // PLAYER_H
