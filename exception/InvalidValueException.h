//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_INVALIDVALUEEXCEPTION_H
#define HAPPYJSON2_INVALIDVALUEEXCEPTION_H

#include <exception>

class InvalidValueException : public std::exception {
public:
    const char *what () const noexcept override {
        return "Invalid Value";
    }
};

#endif //HAPPYJSON2_INVALIDVALUEEXCEPTION_H
