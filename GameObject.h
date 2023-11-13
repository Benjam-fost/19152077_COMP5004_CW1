//
// Created by Ben9H on 13/11/2023.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#include <string>
#include <list>

using namespace std;

class GameObject {
    const string* name;
    const string* description;
    const string* keyword;

public:

    /**
     * Constructs a new GameObject.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    GameObject(const string *_name, const string *_key, const string *_desc);

    /**
     * Removes a destroyed GameObject from the global list if it's there.
     */
    ~GameObject();

    /**
     * Outputs the name and description of the GameObject
     * in standard format.
     */
    void describe() const;

    /**
     * Creates a new GameObject with the given parameters and register it with the static list.
     * @param _name Name of the GameObject.
     * @param _desc Description of the GameObject.
     */
    static GameObject* addGameObject(const string* _name, const string* _key, const string* _desc);
    static void addGameObject(GameObject* object);

    const std::string* getName() const;
};



#endif //TEXTADV_GAMEOBJECT_H
