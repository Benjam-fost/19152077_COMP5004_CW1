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
Room* State::getCurrentRoom() const {
    return this->currentRoom;
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
