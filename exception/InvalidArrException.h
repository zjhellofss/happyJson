//
// Created by fushenshen on 2020/1/4.
//

#ifndef HAPPYJSON2_INVALIDARREXCEPTION_H
#define HAPPYJSON2_INVALIDARREXCEPTION_H

#include <exception>
#include <string>

class InvalidArrException : public std::exception {

public:
    const char *what () const noexcept override {
        return s.data();
    }

    explicit InvalidArrException (std::string s) : s(std::move(s)) {

    }

private:
    std::string s;
};

#endif //HAPPYJSON2_INVALIDARREXCEPTION_H
