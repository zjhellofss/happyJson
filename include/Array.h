//
// Created by fushenshen on 2020/1/4.
//

#ifndef HAPPYJSON2_ARRAY_H
#define HAPPYJSON2_ARRAY_H

#include "Object.h"
#include <vector>
class Array : public Object {

public:
    Array () {
        this->setObjectType(Type::Array);
    }

    const std::vector<std::shared_ptr<Object>> &

    getVec () const {
        return vec;
    }

    void setVec (const std::vector<std::shared_ptr<Object>>

                 &vec) {
        Array::vec = vec;
    }

    void push (Object *val) {
        auto p = std::shared_ptr<Object>(val);
        vec.push_back(p);
    }

private:
    std::vector<std::shared_ptr<Object >> vec;
};

#endif //HAPPYJSON2_ARRAY_H
