#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "Enemy.h"

using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector<Item> itemsInRoom;
    bool enemyInRoom;
    Enemy enemy;
    vector<bool> exits_vector;
    bool canTeleport;


public:
    int numberOfItems();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);

    vector<Item>* getItemsInRoom();
    vector<bool> getExits();
    bool isEnemyInRoom();
    void addEnemy(Enemy *enemy);
    void removeEnemy();
    Enemy& getEnemy();
    string displayEnemy();
};

#endif
