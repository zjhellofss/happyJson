//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_EMPTYVALUEEXCEPTION_H
#define HAPPYJSON2_EMPTYVALUEEXCEPTION_H

#include <exception>

class EmptyValueException : public std::exception {
public:
    const char *what () const noexcept override {
        return "Empty Value";
    }
};

#endif //HAPPYJSON2_EMPTYVALUEEXCEPTION_H
