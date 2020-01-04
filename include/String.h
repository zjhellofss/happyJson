//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_STRING_H
#define HAPPYJSON2_STRING_H

#include "Object.h"
#include <string>

class String : public Object {
public:
    String () {
        this->setObjectType(Type::String);
    }

    String (std::string strVal) : strVal(std::move(strVal)) {
        this->setObjectType(Type::String);
    }

public:
    const std::string &getStrVal () const {
        return strVal;
    }

    void setStrVal (const std::string &strVal) {
        String::strVal = strVal;
    }

private:
    std::string strVal = "";

};

#endif //HAPPYJSON2_STRING_H
