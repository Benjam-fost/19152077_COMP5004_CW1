//
// Created by Ben9H on 13/11/2023.
//

#include "GameObject.h"
#include "wordwrap.h"


GameObject::GameObject(const string *_name, const string *_key, const string *_desc) : name(_name), keyword(_key), description(_desc) {};

GameObject::~GameObject() {
    printf("%s destroyed", name);
}

void GameObject::describe() const {
    wrapOut(description); wrapEndPara();
}

const std::string* GameObject::getName() const {
    return name;
}

const std::string *GameObject::getDescription() const {
    return description;
}

const std::string *GameObject::getKeyword() const {
    return keyword;
}
