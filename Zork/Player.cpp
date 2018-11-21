#include "Player.h"

Player::Player(int health) : Character (health)
{
    magic_level = 50;
    magic_dmg = 23;
    p_weaponPtr = new weapon("Sword", 17, 20);
}


void Player::addItemToInvetory(Item *item)
{
    inventory.push_back(item);
}

void Player::removeItemFromInventory(int pos)
{
    cout << "Inv size = " << inventory.size() << endl;
    inventory.erase(inventory.begin()+pos);
    for(unsigned int i = 0; i < inventory.size(); i++)
    {
        cout << inventory.at(i)->getShortDescription() << endl;
    }
}

void Player::setPlayerInfo(QString name, int age, QString sex)
{
    this->name = name.toStdString();
    this->age = age;
    this->sex = sex.toStdString();
    cout << "name:" << this->name << " age:" << this->age << " sex:" << this->sex <<endl;
}

vector<Item*>& Player::getInventory()
{
    return inventory;
}

string Player::getName()
{
    cout << "Name: " << name << endl;
    return name;
}

int Player::getAge()
{
    return age;
}

void Player::setMagicLevel(int _level)
{
    magic_level = _level;
}

void Player::setMagicDamage(int _damage)
{
    magic_dmg = _damage;
}

string Player::getSex()
{
    return sex;
}

int Player::getMagicLevel()
{
    return magic_level;
}

int Player::getMagicDamage()
{
    return magic_dmg;
}

int Player::getWeaponDamage()
{
    return p_weaponPtr->getDamage();
}

void Player::onDeath()
{
    // TODO show game over screen
}

Player &Player::operator++()
{
    magic_level += 10;

    if(magic_level > MAX_MAGIC_LEVEL)
        magic_level = MAX_MAGIC_LEVEL;

    return *this;
}

Player Player::operator++( int )
{
    magic_level += MAGIC_POTION_AMOUNT;

    if(magic_level > MAX_MAGIC_LEVEL)
        magic_level = MAX_MAGIC_LEVEL;

    return *this;
}

Player &Player::operator--()
{
    magic_level -= MAGIC_POTION_AMOUNT;

    if(magic_level < MIN_MAGIC_LEVEL)
        magic_level = MIN_MAGIC_LEVEL;

    return *this;
}

Player Player::operator--(int)
{
    magic_level -= 10;

    if(magic_level < MIN_MAGIC_LEVEL)
        magic_level = MIN_MAGIC_LEVEL;

    return *this;
}

Player Player::operator+=(const int num)
{
    health += num;

    if(health > MAX_HEALTH)
        health = MAX_HEALTH;

    return *this;
}

Player Player::operator-=(const int num)
{
    health -= num;

    if(health < MIN_HEALTH)
        health = MIN_HEALTH;

    return *this;
}
