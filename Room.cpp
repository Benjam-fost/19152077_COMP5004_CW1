//
// Created by DrMark on 10/2/2017.
//

#include "Room.h"
#include "wordwrap.h"
#include "GameObject.h"

/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;

/**
 * Stores a static list of all objects that can be in a room.
 */
std::list<GameObject*> Room::validRoomObjects;


/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

const string* Room::getName() {
    return name;
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    displayObjects();
    wrapEndPara();
}

void Room::displayObjects() const{
    if (!objects.empty()) {
        printf("Objects you can see:");
        wrapEndPara();
        for (GameObject *object: objects) {
            wrapOut(object->getName());
            wrapEndPara();
        }
    }
    else { printf("You see no objects."); wrapEndPara();}
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

void Room::addValidRoomObject(GameObject* object) {
    bool found = false;
    for (GameObject* obj : validRoomObjects) {
        if ((*obj->getKeyword()) == (*object->getKeyword())) {
            found = true;
        }
    }
    if (!found) validRoomObjects.push_back(object);

}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}

Room* Room::getSouth() const {
    return this->south;
}

Room* Room::getEast() const {
    return this->east;
}

Room* Room::getWest() const {
    return this->west;
}

/**
 * Sets the exits of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}

void Room::setSouth(Room* _south) {
    this->south = _south;
}

void Room::setEast(Room* _east) {
    this->east = _east;
}

void Room::setWest(Room* _west) {
    this->west = _west;
}

void Room::removeRoomObject(GameObject *object) {
    objects.remove(object);
}

void Room::clearObjects() {
    while (!objects.empty()) {
        auto ptr = objects.begin();
        objects.erase(ptr);
    }
}
std::list<GameObject*> Room::getRoomObjects() const {
    return objects;
}

void Room::addRoomObject(GameObject *object) {
    addValidRoomObject(object);
    objects.push_back(object);
}

bool Room::isNotValid(string *key) {
    for (GameObject* i : validRoomObjects) {
        if ((*i->getKeyword()) == (*key)) {
            return false;
        }
    }
    return true;
}

list<Room*> Room::getRooms() {
    return rooms;
}

list<GameObject *> Room::getValidRoomObjects() {
    return validRoomObjects;
}
