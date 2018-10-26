/*#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "ZorkUL.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;


class Character {
private:
	string description;
	 vector < string > itemsInCharacter;
public:
    void addItems(string Item);




public:
	Character(string description);
	string shortDescription();
	string longDescription();

};

#endif CHARACTER_H_*/

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include <string>

class Character {
private:

protected:
    int health;

public:
    //Character();
    Character(int health);

    int getHealth();
    void setHealth(int h);

    virtual void onDeath() = 0;
};

#endif //CHARACTER_H_
