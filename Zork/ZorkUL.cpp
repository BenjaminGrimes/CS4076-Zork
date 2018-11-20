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
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

	a = new Room("a");
        a->setRoomDescription("In room a");
        a->addItem(new Potion(Potion::PotionType::health_potion));
        a->addItem(new Potion(Potion::PotionType::magic_potion));
	b = new Room("b");
        b->setRoomDescription("In room b");
        b->addItem(new Potion(Potion::PotionType::magic_potion));
        b->addItem(new Potion(Potion::PotionType::health_potion));
	c = new Room("c");
        c->setRoomDescription("In room c");
	d = new Room("d");
        d->setRoomDescription("In room d");
        //d->addEnemy(new Enemy());
	e = new Room("e");
        e->setRoomDescription("In room e");
	f = new Room("f");
        f->setRoomDescription("In room f");
	g = new Room("g");
        g->setRoomDescription("In room g");
    h = new Room("h");
        h->setRoomDescription("In room h");
    i = new Room("i");
        i->setRoomDescription("In room i");
    j = new Room("j");
        j->setRoomDescription("In room j");


    //         (N, E, S, W)
	a->setExits(f, b, d, c);
	b->setExits(NULL, NULL, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
	d->setExits(a, e, NULL, i);
	e->setExits(NULL, NULL, NULL, d);
	f->setExits(NULL, g, a, h);
	g->setExits(NULL, NULL, NULL, f);
	h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, j, NULL);
    j->setExits(i, NULL, NULL, NULL);

    currentRoom = a;

    rooms.push_back(a);
    rooms.push_back(b);
    rooms.push_back(c);
    rooms.push_back(d);
    rooms.push_back(e);
    rooms.push_back(f);
    rooms.push_back(g);
    rooms.push_back(h);
    rooms.push_back(i);
    rooms.push_back(j);

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
