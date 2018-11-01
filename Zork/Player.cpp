#include "Player.h"

Player::Player(int health) : Character (health)
{

}

void Player::addItemToInvetory(Item &item)
{
    // TODO validate item

    inventory.push_back(item);
}

void Player::removeItemFromInventory(int pos)
{
    cout << "Inv size = " << inventory.size() << endl;
    inventory.erase(inventory.begin()+pos);
    for(int i = 0; i < inventory.size(); i++)
    {
        cout << inventory.at(i).getShortDescription() << endl;
    }
    /*for(int i = 0; i < inventory.size(); i++)
    {
        // TODO Check if items are the same
        if(&inventory.at(i) == &item)
            cout << "Found item" << endl;
        else
            cout << &inventory.at(i) << " != " << &item << endl;
    }*/
}

vector<Item>& Player::getInventory()
{
    return inventory;
}

void Player::onDeath()
{
    // TODO show game over screen
}
