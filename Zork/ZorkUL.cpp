#include <iostream>

using namespace std;
#include "ZorkUL.h"

ZorkUL::ZorkUL() : player(100)
{
    setInCombat(false);
	createRooms();
}

void ZorkUL::RandomizeEnemy()
{
    int randRoom = getRandom<int>(9)+1;
    rooms.at(randRoom)->addEnemy(new Enemy());
    cout << "Enemy add to room " << randRoom;
}

void ZorkUL::createRooms()
{
    Room *cave = new Room("Cave");
    cave->setRoomDescription("In Cave");
    cave->addItem(new Potion(Potion::PotionType::health_potion));
    cave->addItem(new Potion(Potion::PotionType::magic_potion));

    Room *woods = new Room("Woods");
    woods->setRoomDescription("In Woods");
    woods->addItem(new Potion(Potion::PotionType::magic_potion));
    woods->addItem(new Potion(Potion::PotionType::health_potion));

    Room *abandoned_house = new Room("Abandoned House");
    abandoned_house->setRoomDescription("In Abandoned House");

    Room *field = new Room("Field");
    field->setRoomDescription("In Field");
    //d->addEnemy(new Enemy());

    Room *meadow = new Room("Meadow");
    meadow->setRoomDescription("In room e");

    Room *abandoned_mill = new Room("Abandoned Mill");
    abandoned_mill->setRoomDescription("In room f");

    Room *bridge = new Room("Bridge");
    bridge->setRoomDescription("In room g");

    Room *empty_well = new Room("Empty Well");
    empty_well->setRoomDescription("In room h");

    Room *stables = new Room("Stables");
    stables->setRoomDescription("In room i");

    Room *abandoned_town = new Room("Abandoned Town");
    abandoned_town->setRoomDescription("In room j");

    Room *destroyed_fort = new Room("Destroyed Fort");
    destroyed_fort->setRoomDescription("");

    Room *ridge = new Room("Ridge");
    ridge->setRoomDescription("");

    Room *mountains = new Room("Mountains");
    mountains->setRoomDescription("");

    Room *valley = new Room("Valley");
    valley->setRoomDescription("");

    Room *shoreline = new Room("Shoreline");
    shoreline->setRoomDescription("");

    Room *river = new Room("River");
    river->setRoomDescription("");

    Room *island = new Room("Island");
    island->setRoomDescription("");

    Room *beach = new Room("Beach");
    beach->setRoomDescription("");

    Room *rocky_hills = new Room("Rocky Hills");
    rocky_hills->setRoomDescription("");

    Room *graveyard = new Room("Graveyard");
    graveyard->setRoomDescription("");

    Room *old_castle = new Room("Old Castle");
    old_castle->setRoomDescription("");

    Room *grassland = new Room("Grassland");
    grassland->setRoomDescription("");

    Room *home = new Room("Home");
    home->setRoomDescription("");

    // (N, E, S, W)
    cave->setExits(woods, field, NULL, NULL);
    woods->setExits(NULL, abandoned_house, cave, NULL);
    abandoned_house->setExits(NULL, meadow, field, woods);
    field->setExits(abandoned_house, stables, NULL, cave);
    meadow->setExits(NULL, abandoned_mill, NULL, abandoned_house);
    abandoned_mill->setExits(NULL, NULL, bridge, meadow);
    bridge->setExits(abandoned_mill, NULL, empty_well, NULL);
    empty_well->setExits(bridge, NULL, NULL, abandoned_town);
    stables->setExits(NULL, NULL, abandoned_town, field);
    abandoned_town->setExits(stables, empty_well, destroyed_fort, NULL);
    destroyed_fort->setExits(abandoned_house, NULL, ridge, NULL);
    ridge->setExits(destroyed_fort, mountains, NULL, NULL);
    mountains->setExits(NULL, NULL, valley, ridge);
    valley->setExits(mountains, NULL, NULL, shoreline);
    shoreline->setExits(NULL, valley, NULL, river);
    river->setExits(island, shoreline, NULL, NULL);
    island->setExits(beach, NULL, river, NULL);
    beach->setExits(rocky_hills, NULL, island, old_castle);
    rocky_hills->setExits(NULL, NULL, beach, graveyard);
    graveyard->setExits(NULL, rocky_hills, old_castle, NULL);
    old_castle->setExits(graveyard, beach, grassland, NULL);
    grassland->setExits(old_castle, NULL, home, NULL);
    home->setExits(grassland, NULL, NULL, NULL);

    currentRoom = cave;

    rooms.push_back(cave);
    rooms.push_back(woods);
    rooms.push_back(abandoned_house);
    rooms.push_back(field);
    rooms.push_back(meadow);
    rooms.push_back(abandoned_mill);
    rooms.push_back(bridge);
    rooms.push_back(empty_well);
    rooms.push_back(stables);
    rooms.push_back(abandoned_town);
    rooms.push_back(destroyed_fort);
    rooms.push_back(ridge);
    rooms.push_back(mountains);
    rooms.push_back(valley);
    rooms.push_back(shoreline);
    rooms.push_back(river);
    rooms.push_back(island);
    rooms.push_back(beach);
    rooms.push_back(rocky_hills);
    rooms.push_back(graveyard);
    rooms.push_back(old_castle);
    rooms.push_back(grassland);
    rooms.push_back(home);

    RandomizeEnemy();
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play()
{
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}

void ZorkUL::printWelcome()
{
	cout << "start"<< endl;
	cout << "info for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command)
{
    if (command.isUnknown())
    {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
    {
		printHelp();
    }
	else if (commandWord.compare("map") == 0)
    {
        printMap();
    }
    else if(commandWord.compare("teleport") == 0)
    {
        teleport();
    }
	else if (commandWord.compare("go") == 0)
    {
		goRoom(command);
    }
    else if (commandWord.compare("take") == 0)
    {
        // TODO add item to character inventory.
        if (!command.hasSecondWord())
        {
            cout << "incomplete input"<< endl;
        }
        else if (command.hasSecondWord())
        {
            cout << "you're trying to take " + command.getSecondWord() << endl;
            int location = currentRoom->isItemInRoom(command.getSecondWord());

            if (location  < 0 )
                cout << "item is not in room" << endl;
            else
            {
                cout << "item is in room" << endl;

            }
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }
    else if (commandWord.compare("put") == 0)
    {
        // TODO add put feature
        cout << "PUT" << endl;
        cout << "you're trying to put " << command.getSecondWord() << endl;
    }
    else if(commandWord.compare("inventory") == 0)
    {
        //TODO print out items in character inventory
        cout << "You are carrying: " << endl;
    }
    /*
    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
    */
    else if (commandWord.compare("quit") == 0)
    {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}

/** COMMANDS **/
void ZorkUL::printHelp()
{
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::printMap()
{
    cout << "[h] --- [f] --- [g]" << endl;
    cout << "         |         " << endl;
    cout << "         |         " << endl;
    cout << "[c] --- [a] --- [b]" << endl;
    cout << "         |         " << endl;
    cout << "         |         " << endl;
    cout << "[i] --- [d] --- [e]" << endl;
    cout << " |                 " << endl;
    cout << " |                 " << endl;
    cout << "[j]                " << endl;
}

void ZorkUL::teleport()
{
    // TODO Check if teleporting to currentRoom.
    int index = rand() % rooms.size();
    Room* nextRoom = rooms[index];
    currentRoom = nextRoom;
    cout << currentRoom->longDescription() << endl;
}

void ZorkUL::goRoom(Command command)
{
    if (!command.hasSecondWord())
    {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
    {
		cout << "underdefined input"<< endl;
    }
    else
    {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
}

Room* ZorkUL::getCurrentRoom()
{
    return currentRoom;
}

string ZorkUL::getCurrentRoomName()
{
    return currentRoom->shortDescription();
}

string ZorkUL::getCurrentRoomDescription()
{
    // TODO return story text, not just description of room.
    // i.e. dont need to know current room or know the exits
    return currentRoom->longDescription();
}

string ZorkUL::go(string direction)
{
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
    {
        // No room in that direction
        return "ERROR";
    }
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}

bool ZorkUL::isInCombat()
{
    return isInCombat();
}

void ZorkUL::setInCombat(bool inCombat)
{
    this->inCombat = inCombat;
}
