#include "Enemy.h"

Enemy::Enemy(int health) : Character (health)
{

}

void Enemy::onDeath()
{
    // TODO remove enemy from room
}
