
#include <iostream>
#include <memory>
#include <forward_list>
#include "State.h"
#include "Room.h"
#include "wordwrap.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r5 = new Room(&r5name, &r5desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r1 = new Room(&r1name, &r1desc);
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    r1->setNorth(r2);
    r1->setSouth(r3);
    r1->setEast(r4);
    r1->setWest(r5);
    r2->setSouth(r1);
    r3->setNorth(r1);
    r4->setWest(r1);
    r5->setEast(r1);
    r1->addObject(new GameObject(&largeCupName,&largeCupKey,&largeCupDesc));
    r1->addObject(new GameObject(&silverSpoonName,&silverSpoonKey,&silverSpoonDesc));
    r4->addObject(new GameObject(&largeCupName,&largeCupKey,&largeCupDesc));
    r5->addObject(new GameObject(&shinyBowlName,&shinyBowlKey,&shinyBowlDesc));
    r5->addObject(new GameObject(&fluffyPillowName,&fluffyPillowKey,&fluffyPillowDesc));
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}

/**
 * Finds a GameObject using its keyword.
 * returns nullptr if not found.
 * @param key The keyword associated with the target object.
 * @param flag A list of bool flags for error checking, refer to declaration for details.
 * @return GameObject
 */
static GameObject* findObject(string *key, bool *flag) {
    GameObject* found = nullptr;
    for (GameObject* object : currentState->getInventory()) {
        if ((*object->getKeyword()) == (*key)) {
            found = object;
            flag[1] = true; flag[2] = false;
        }
    }
    for (GameObject* object : currentState->getCurrentRoom()->getObjects()) {
        if ((*object->getKeyword()) == (*key)) {
            found = object;
            flag[0] = true; flag[2] = false;
        }
    }
    return found;
}

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    /**
     * Bool array for error reporting in findObject().
     * flag[0] indicates if the GameObject found is in currentRoom.
     * flag[1] indicates if the GameObject found is in inventory.
     * flag[2] indicates if the GameObject is a nullptr/does not exist.
     */
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        bool flag[3] {false, false, true};
        inputCommand(&commandBuffer);
        uint8_t buffLength = commandBuffer.length();
        string key;
        GameObject *object;

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        if (endOfVerb < buffLength) {
            key = commandBuffer.substr(endOfVerb+1, buffLength);
            object = findObject(&key, flag);
        }
        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */

        if ((commandBuffer.compare(0,buffLength,"north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            Room *northRoom = currentState->getCurrentRoom()->getNorth(); /* Gets room */
            currentState->goTo(northRoom); /* Sets room, input validation in State.cpp, line 31 onwards */
        }
        else if ((commandBuffer.compare(0, endOfVerb, "south") == 0) || (commandBuffer.compare(0, endOfVerb, "s") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            Room *southRoom = currentState->getCurrentRoom()->getSouth(); /* Gets room */
            currentState->goTo(southRoom);
        }
        else if ((commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)) {
            commandOk = true;
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            currentState->goTo(eastRoom);
        }
        else if ((commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {
            commandOk = true;
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            currentState->goTo(westRoom);
        }
        /*
         * Implement std::map<string:Room>
         * int8_t x and int8_t y in State
         * refer to email.

         switch(1) {
            case 1:
                break;
            case 2:
                break;
        }
         */
        /**
         * Removes an object from currentRoom and adds it into inventory.
         * Checks if the user has entered an object and where the object is.
         * Displays unique error messages depending on State and user input using a bool array, flag[].
         */
        if ((commandBuffer.compare(0, endOfVerb, "get") == 0)) {
            commandOk = true;
            if (flag[2]) {
                wrapOut(&noObject); wrapEndPara();
            }
            else if (flag[1]) {
                wrapOut(&inInventory); wrapEndPara();
            }
            else if (!flag[0]) {
                wrapOut(&notInRoom); wrapEndPara();
            }
            else {
                currentState->addObject(object);
                currentState->getCurrentRoom()->removeRoomObject(object);
                wrapOut(&got); wrapEndPara();
            }
        }

        /**
         * Removes an object from inventory and adds it to the Room.
         * Checks if the user has entered an object and where the object is.
         * Displays unique error messages depending on State and user input.
         */
        else if ((commandBuffer.compare(0, endOfVerb, "drop") == 0)) {
            commandOk = true;
            if (flag[2]) {
                wrapOut(&noObject);
                wrapEndPara();
            }
            else if (flag[0]) {
                wrapOut(&inRoom); wrapEndPara();
            }
            else if (!flag[1]) {
                wrapOut(&notInInventory); wrapEndPara();
            }
            else {
                currentState->removeInvObject(object);
                currentState->getCurrentRoom()->addObject(object);
                wrapOut(&dropped); wrapEndPara();
            }
        }

        /**
         * Calls a function to examine an object.
         * Outputs the description of the object with the keyword entered.
         */
        else if ((commandBuffer.compare(0, endOfVerb, "examine") == 0)) {
            commandOk = true;
            wrapEndPara();
            if (!flag[2]) {
                wrapOut(object->getName());
                wrapEndPara();
                object->describe();
            }
            else {wrapOut(&noObject); wrapEndPara();}
        }

        /**
         * Calls a function to display the player inventory.
         * Outputs a message if inventory is empty.
         */
        else if ((commandBuffer.compare(0, endOfVerb, "inventory") == 0)) {commandOk = true; currentState->displayInventory();}

        /* Quit command */
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}