//
// Created by DrMark on 10/2/2017.
//

#include "State.h"
#include "strings.h"
#include "wordwrap.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    if (target != nullptr) {
        this->currentRoom = target;
        this->announceLoc();
    }
    else {
        wrapOut(&badExit);      /* Output the "can't go there" message */
        wrapEndPara();
    }

}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() {
    return currentRoom;
}

void State::displayInventory() const {
    if (!inventory.empty()) {
        for (GameObject *object: inventory) {
            wrapOut(object->getName());
            wrapEndPara();
        }
    }
    else {wrapOut(&emptyInventory); wrapEndPara();}
}
/**
 * Gets the inventory list.
 * @return inventory
 */
std::list<GameObject *> &State::getInventory() {
    return inventory;
}
/**
 * Adds an object to the inventory.
 * @param object
 */
void State::addInvObject(GameObject* object) {
    inventory.push_back(object);
}

void State::removeInvObject(GameObject* object) {
    inventory.remove(object);
}