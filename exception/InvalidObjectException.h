//
// Created by fushenshen on 2020/1/4.
//

#ifndef HAPPYJSON2_INVALIDOBJECTEXCEPTION_H
#define HAPPYJSON2_INVALIDOBJECTEXCEPTION_H

#include <exception>
#include <string>

class InvalidObjectException: public std::exception {

public:
    const char *what () const noexcept override {
        return s.data();
    }

    explicit InvalidObjectException (std::string s) : s(std::move(s)) {

    }

private:
    std::string s;
};

#endif //HAPPYJSON2_INVALIDOBJECTEXCEPTION_H
