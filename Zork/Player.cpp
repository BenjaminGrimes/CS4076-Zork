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

void Player::setPlayerInfo(QString name, int age, QString sex)
{
    this->name = name.toStdString();
    this->age = age;
    this->sex = sex.toStdString();

    cout << "name:" << this->name << " age:" << this->age << " sex:" << this->sex << endl;
}

vector<Item>& Player::getInventory()
{
    return inventory;
}

void Player::onDeath()
{
    // TODO show game over screen
}

Player &Player::operator++()
{
    health += 10;

    if(health > 100)
        health = 0;

    return *this;
}

Player Player::operator++( int )
{
    health += 10;

    if(health > 100)
        health = 100;
    if(health < 0)
        health = 0;

    return *this;
}

Player &Player::operator--()
{
    health -= 10;

    if(health > 100)
        health = 100;
    if(health < 0)
        health = 0;

    return *this;
}

Player Player::operator--(int)
{
    health -= 10;

    if(health > 100)
        health = 100;
    if(health < 0)
        health = 0;

    return *this;
}
