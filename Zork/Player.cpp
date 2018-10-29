#include "Player.h"

Player::Player(int health) : Character (health)
{

}

void Player::addItemToInvetory(Item item)
{
    // TODO validate item

    inventory.push_back(item);
}

vector<Item>& Player::getInventory()
{
    return inventory;
}

void Player::onDeath()
{
    // TODO show game over screen
}
