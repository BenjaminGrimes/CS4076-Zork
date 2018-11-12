#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ZorkUL {
private:
	Parser parser;
    vector<Room*> rooms;

    void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
    void printMap();
    //void teleport();
	void goRoom(Command command);
    void createItems();
    void displayItems();

public:
    Room *currentRoom;
    Player player;

	ZorkUL();
	void play();
    void teleport();
    Room* getCurrentRoom();
    string getCurrentRoomName();
    string getCurrentRoomDescription();
    template <typename T> T getRandom(T num){
        qsrand(time(NULL));
        return qrand()%num;
    }

	string go(string direction);
};

#endif /*ZORKUL_H_*/
