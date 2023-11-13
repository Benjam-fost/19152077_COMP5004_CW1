//
// Created by Ben9H on 13/11/2023.
//

#include "GameObject.h"

GameObject::GameObject(const string *_name, const string *_key, const string *_desc) : name(_name), keyword(_key), description(_desc) {
    ;
}

GameObject::~GameObject() {
    printf("%s destroyed", name);
}

void GameObject::describe() const {
    printf("%s", description);
}

GameObject *GameObject::addGameObject(const string *_name, const string *_key, const string *_desc) {

    return nullptr;
}

void GameObject::addGameObject(GameObject *object) {

}

const std::string* GameObject::getName() const {
    return name;
}
