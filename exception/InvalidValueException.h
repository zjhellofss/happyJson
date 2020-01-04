//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_INVALIDVALUEEXCEPTION_H
#define HAPPYJSON2_INVALIDVALUEEXCEPTION_H

#include <exception>
#include <string>

class InvalidValueException : public std::exception {
public:
    const char *what () const noexcept override {
        return s.data();
    }

    explicit InvalidValueException (std::string ss) : s(std::move(ss)) {

    }

private:
    std::string s;
};

#endif //HAPPYJSON2_INVALIDVALUEEXCEPTION_H
