#ifndef RACE_H
#define RACE_H
#include <string>
using namespace std;
class race {

private:
    int att_magicDamage;
    int att_magicLevel;
    int att_health;

    //int att_damage;

public:
    race();
    string type;
    void setMagicDamage( int _magicDmg);
    void setMagicLevel(int _magicLvl);
    void setHealth( int _health);
   //void setDamage( int _damage);
    string getType();
    int getMagicDamage();
    int getMagicLevel();
    int getHealth();
   // int getDamage();


};
#endif // RACE_H
