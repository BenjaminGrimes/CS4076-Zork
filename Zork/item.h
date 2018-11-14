#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

#define DEFAULT_DAMAGE 0

class Item {
private:

	string longDescription;
	int weightGrams;
	float value;
	bool weaponCheck;

public:
    string description;

    Item (string description);
    Item (string description, int inWeight, float inValue);

    string getShortDescription();
    string getLongDescription();
	int getWeight();
	void setWeight(int weightGrams);
    float getValue();
	void setValue(float value);
	int getWeaponCheck();
	void setWeaponCheck(int weaponCheck);
    virtual int getDamage();
};

#endif /*ITEM_H_*/
