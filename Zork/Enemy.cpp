#include "Enemy.h"

Enemy::Enemy() : Character (MAX_HEALTH)
{
    name = "ENEMY";
    dmg = 5;
}

void Enemy::onDeath()
{
    // TODO remove enemy from room
}

int Enemy::getDamage()
{
    return dmg;
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
    setHealth(getHealth()-10);

    /*
    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
    if(health < MIN_HEALTH)
        health = MIN_HEALTH;
    */
    return *this;
}

Enemy Enemy::operator--(int)
{
    setHealth(getHealth()-10);

    return *this;
}

Enemy Enemy::operator+=(const int num)
{
    health += num;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;
    if(health < MIN_HEALTH)
        health = MIN_HEALTH;

    return *this;
}

Enemy Enemy::operator-=(const int num)
{
    health -= num;

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
