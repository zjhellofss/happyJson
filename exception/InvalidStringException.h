//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_INVALIDSTRINGEXCEPTION_H
#define HAPPYJSON2_INVALIDSTRINGEXCEPTION_H

#include <exception>

class InvalidStringException : public std::exception {
public:
    const char *what () const noexcept override {
        return "invalid string Value";
    }
};

#endif //HAPPYJSON2_INVALIDSTRINGEXCEPTION_H
