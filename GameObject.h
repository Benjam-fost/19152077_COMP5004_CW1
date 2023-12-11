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

    bool operator<(const GameObject& object) const;
    bool operator>(const GameObject& object) const;
    bool operator==(const GameObject& object) const;
    bool operator!=(const GameObject& object) const;

    /**
     * Removes a destroyed GameObject from the global list if it's there.
     */
    ~GameObject();

    /**
     * Outputs the name and description of the GameObject.
     * in standard format.
     */
    void describe() const;
    /**
     * Returns the name of the object.
     * @return name
     */
    const std::string* getName() const;
    /**
     * Returns the description of the object.
     * @return description
     */
    const std::string* getDescription() const;
    /**
     * Returns the keyword of the object.
     * @return keyword
     */
    const std::string* getKeyword() const;
};



#endif //TEXTADV_GAMEOBJECT_H
