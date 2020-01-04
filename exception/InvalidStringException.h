#include <utility>

//
// Created by fushenshen on 2020/1/3.
//

#ifndef HAPPYJSON2_INVALIDSTRINGEXCEPTION_H
#define HAPPYJSON2_INVALIDSTRINGEXCEPTION_H

#include <exception>
#include <string>

class InvalidStringException : public std::exception {
public:
    const char *what () const noexcept override {
        return s.data();
    }

    explicit InvalidStringException (std::string ss) : s(std::move(ss)) {

    }

private:
    std::string s;

};

#endif //HAPPYJSON2_INVALIDSTRINGEXCEPTION_H
