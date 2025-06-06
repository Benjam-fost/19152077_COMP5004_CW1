//
// Created by DrMark on 10/2/2017.
//


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include <set>
#include "GameObject.h"

using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
      * List storing all objects in a room.
      */
    std::list<GameObject*> objects;
    /**
     * Pointers to rooms from this one.
     */
   Room* north;
   Room* south;
   Room* east;
   Room* west;
public:
   /**
    * Constructs a new Room.
    * @param _name Name of the room.
    * @param _desc Description of the room.
    */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;
    void displayObjects() const;
    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;
    static std::list<GameObject*> validRoomObjects;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);

    std::list<GameObject*> getRoomObjects() const;
    Room* getNorth() const;
    Room* getSouth() const;
    Room* getEast() const;
    Room* getWest() const;
    void setNorth(Room* _north);
    void setSouth(Room* _south);
    void setEast(Room* _east);
    void setWest(Room* _west);

    void addRoomObject(GameObject* object);
    void removeRoomObject(GameObject *object);

    static void addValidRoomObject(GameObject *object);
    static std::list<GameObject*> getValidRoomObjects();
    static bool isNotValid(string *key);

    const string *getName();
    static std::list<Room*> getRooms();

    void clearObjects();
};

#endif //TEXTADV_ROOM_H
