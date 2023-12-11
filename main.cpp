
#include <iostream>
#include <fstream>
#include <memory>
#include <forward_list>
#include <sstream>
#include "State.h"
#include "Room.h"
#include "wordwrap.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;
string fileName = "autosave.csv";

std::string encrypt(std::string data) {
    int i = 0;
    char temp;
    while (i+1 < data.length()) {
        temp = data[i+1];
        data[i+1] = data[i];
        data[i] = temp;
        i += 2;
    }
    return data;
}
std::string decrypt(std::string data) {
    int i = 0;
    char temp;
    while (i+1 < data.length()) {
        temp = data[i];
        data[i] = data[i+1];
        data[i+1] = temp;
        i += 2;
    }
    return data;
}

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
    r1->addRoomObject(new GameObject(&largeCupName, &largeCupKey, &largeCupDesc));
    r1->addRoomObject(new GameObject(&silverSpoonName, &silverSpoonKey, &silverSpoonDesc));
    r4->addRoomObject(new GameObject(&largeCupName, &largeCupKey, &largeCupDesc));
    r5->addRoomObject(new GameObject(&shinyBowlName, &shinyBowlKey, &shinyBowlDesc));
    r5->addRoomObject(new GameObject(&fluffyPillowName, &fluffyPillowKey, &fluffyPillowDesc));
}

void save() {
    std::ofstream sFile(fileName);

    if(sFile.is_open()) {
        Room* room = currentState->getCurrentRoom();
        sFile << encrypt((*room->getName())) << endl; // Saving currentRoom

        int i = 1;
        list<GameObject*> inv = currentState->getInventory();
        for (GameObject *object : inv) { // Saving inventory
            sFile << encrypt(*object->getKeyword());
            if (i != inv.size()) {
                sFile << ",";
            }
            else sFile << "\n";
            i++;
        }

        list<Room*> rooms = Room::getRooms();
        for (Room* r: rooms) { // Saving GameObjects in rooms
            list<GameObject*> objects = r->getRoomObjects();
            sFile << encrypt((*r->getName()));
            if (!objects.empty()) {
                for (GameObject *object: objects) {
                    sFile << "," << encrypt((*object->getKeyword()));
                }
            }
            sFile << endl;
        }
    }

    if (sFile.good()) {
        cout << "Game saved successfully" << endl;
    }
    else cout << "Error saving game" << endl;
    sFile.close();
}
Room* findRoom(const string& name) {
    list<Room*> list = Room::getRooms();
    Room* room;
    for (auto ptr = list.begin(); ptr != list.end(); ptr++) {
        if (*(*ptr)->getName() == name) room = *ptr;
    }
    return room;

    /*
    Room* ptr;
    for (Room* room : Room::getRooms()) {
        if ((*room->getName()) == name) ptr = room;
    }
    return ptr;
     */
}

bool load() {
    string buffer;
    std::ifstream lFile(fileName);

    if (lFile.fail()) {
        cout << "Invalid file: " << fileName << endl << endl;
        return false;
    }

    if (lFile.is_open()) {
        getline(lFile, buffer);
        currentState = new State(findRoom(decrypt(buffer)));

        getline(lFile, buffer);
        istringstream iss(buffer);
        while (getline(iss, buffer, ',')) {
            buffer = decrypt(buffer);
            for (GameObject *object: Room::getValidRoomObjects()) {
                if ((*object->getKeyword()) == buffer) {
                    currentState->addInvObject(object);
                }
            }
        }

        while (getline(lFile, buffer)) {
            iss.clear(); iss.str(buffer);
            getline(iss, buffer, ',');
            Room* room = findRoom(decrypt(buffer));
            room->clearObjects();
            while (getline(iss, buffer, ',')) {
                for (GameObject *object: Room::getValidRoomObjects()) {
                    if ((*object->getKeyword()) == decrypt(buffer)) {
                        room->addRoomObject(object);
                    }
                }
            }
        }
        lFile.close();
        return true;
    }
    else return false;
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
    for (GameObject* object : currentState->getCurrentRoom()->getRoomObjects()) {
        if ((*object->getKeyword()) == (*key)) {
            found = object;
            flag[0] = true; flag[2] = false;
        }
    }
    if (flag[2]) {
        flag[2] = Room::isNotValid(key);
    }
    return found;
}

void menu() {
    bool chosen = false;
    string temp;
    char choice;
    while (!chosen) {
        printf("MAIN MENU:\n\n(S)tart new game   |   (L)oad game\n\n");
        inputCommand(&temp);
        choice = temp[0];
        switch (choice) {
            case 'S':
            case 's':
                printf("\nStarting new game\n\n");
                return;
            case 'L':
            case 'l':
                cout << "\n***LOAD***" << endl;
                cout << "Enter the file name of your save file: ";
                inputCommand(&fileName);
                chosen = true;
                if (!load()) printf("\nStarting new game\n");
                break;
            default:
                printf("\nPlease enter:\nS to start a new game\nL to load a save file\n");
        }
    }
}

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;

    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        /**
         * Bool array for error reporting in findObject().
         * flag[0] indicates if the GameObject found is in currentRoom.
         * flag[1] indicates if the GameObject found is in inventory.
         * flag[2] indicates if the GameObject is a nullptr/does not exist.
         */
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

        /**
         * Removes an object from currentRoom and adds it into inventory.
         * Checks if the user has entered an object and where the object is.
         * Displays unique error messages depending on State and user input using a bool array, flag[].
         */
        if ((commandBuffer.compare(0, endOfVerb, "get") == 0)) {
            commandOk = true;
            if (!flag[2] && !flag[1] && !flag[0]) {
                wrapOut(&notFound); wrapEndPara();
            }
            else if (flag[2]) {
                wrapOut(&noObject); wrapEndPara();
            }
            else if (!flag[0]) {
                wrapOut(&notInRoom); wrapEndPara();
            }
            else if (flag[1]) {
                wrapOut(&inInventory); wrapEndPara();
            }

            else {
                currentState->addInvObject(object);
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
                currentState->getCurrentRoom()->addRoomObject(object);
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


        if ((commandBuffer.compare(0, endOfVerb, "save") == 0)) {
            commandOk = true;
            printf("\n***SAVE***\n");
            printf("Please enter a file name: ");
            inputCommand(&fileName);
            save();
        }
        if ((commandBuffer.compare(0, endOfVerb, "load") == 0)) {
            commandOk = true;
            printf("\n***LOAD***\n");
            printf("Please enter a file name: ");
            inputCommand(&fileName);
            if (load()) {
                cout << endl << "Load successful" << endl;
                currentState->announceLoc();
            }
            else cout << endl << "Error loading save file" << endl;
        }

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
    menu();
    currentState->announceLoc();
    gameLoop();
    fileName = "autosave.csv";
    save(); // This implements autosave functionality
    // save() is implemented in gameLoop() also, which asks for filename
    return 0;
}