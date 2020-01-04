#include <utility>

//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_OBJECT_H
#define HAPPYJSON2_OBJECT_H

#include <string>
#include <map>

#include <iostream>
#include <cassert>
#include "Type.h"

class Object {

public:

    Object () {}

    Object (std::string objectName, Type ObjectType) :
            objectName(std::move(objectName)), objectType(ObjectType) {
    }


    virtual ~Object () {

    }

public:
    Object *getValue (const std::string &name) const {
        auto val = values.find(name);
        if (val != values.end()) {
            return val->second.get();
        } else {
            return nullptr;
        }
    }


    virtual void setValue (const std::string &name, Object *object) {
        if (values.empty()) {
            values.insert({name, std::shared_ptr<Object>(object)});
        } else {
            auto val = values.find(name);
            if (val == this->values.end()) {
                values.insert({name, std::shared_ptr<Object>(object)});
            } else {
                return;
            }
        }
    }

    const std::string &getObjectName () const {
        return objectName;
    }

    void setObjectName (const std::string &objectName) {
        Object::objectName = objectName;
    }

    Type getObjectType () const {
        return objectType;
    }

    void setObjectType (Type ObjectType) {
        Object::objectType = ObjectType;
    }

    const std::map<std::string, std::shared_ptr<Object>> &

    getValues () const {
        return values;
    }


private:
    std::string objectName = "";
    std::map<std::string, std::shared_ptr<Object>> values;
    Type objectType;
};


#endif //HAPPYJSON2_OBJECT_H
