//
// Created by Ben9H on 13/11/2023.
//

#include "GameObject.h"
#include "wordwrap.h"


GameObject::GameObject(const string *_name, const string *_key, const string *_desc) : name(_name), keyword(_key), description(_desc) {};

bool GameObject::operator<(const GameObject& object) const{
    if (this->keyword < object.keyword) return true;
    else if (this->keyword > object.keyword) return false;
    return false;
}
bool GameObject::operator>(const GameObject& object) const{
    if (this->keyword > object.keyword) return true;
    else if (this->keyword < object.keyword) return false;
    return false;
}

bool GameObject::operator==(const GameObject& object) const{
    return this->keyword == object.keyword;
}

bool GameObject::operator!=(const GameObject& object) const{
    return this->keyword != object.keyword;
}

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
