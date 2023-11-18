//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H

#include <cstdint>
#include "GameObject.h"


#include "Room.h"

class State {
    Room *currentRoom;
protected:
    std::list<GameObject*> inventory;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom();
    std::list<GameObject*> &getInventory();
    void displayInventory() const;

    void removeInvObject(string* key);
    void addObject(GameObject* object);

    void removeObject(GameObject *object);
};


#endif //TEXTADV_STATE_H
