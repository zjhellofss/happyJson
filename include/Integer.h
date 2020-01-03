//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_INTEGER_H
#define HAPPYJSON2_INTEGER_H

#include "Object.h"

class Integer : public Object {
public:
    Integer () {

    }

    explicit Integer (double val) : val(val) {}

    double getVal () const {
        return val;
    }

    void setVal (double val) {
        Integer::val = val;
    }

private:
    double val = 0.0;

};


#endif //HAPPYJSON2_INTEGER_H
