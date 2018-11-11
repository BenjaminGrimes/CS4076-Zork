#include "Enemy.h"

Enemy::Enemy() : Character (MAX_HEALTH)
{
    name = "ENEMY";
}

void Enemy::onDeath()
{
    // TODO remove enemy from room
}

Enemy &Enemy::operator++()
{
    health += 10;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
    if(health < MIN_HEALTH)
        health = MIN_HEALTH;

    return *this;
}

Enemy Enemy::operator++(int)
{
    health += 10;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
    if(health < MIN_HEALTH)
        health = MIN_HEALTH;

    return *this;
}

Enemy &Enemy::operator--()
{
    health -= 10;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
    if(health < MIN_HEALTH)
        health = MIN_HEALTH;

    return *this;
}

Enemy Enemy::operator--(int)
{
    health -= 10;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
    if(health < MIN_HEALTH)
        health = MIN_HEALTH;

    return *this;
}

string Enemy::getDescription()
{
    string temp = "Enemy is here! Health = " + std::to_string(health);
    return temp;
}

string Enemy::getName()
{
    return name;
}
