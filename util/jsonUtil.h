//
// Created by fushenshen on 2019/12/31.
//

#ifndef HAPPYJSON_JSON_UTIL_H
#define HAPPYJSON_JSON_UTIL_H

#include "../include/json_object.h"
#include "../include/json_string.h"
#include "../include/json_integer.h"
#include "../include/json_array.h"
#include <string>

namespace JsonUtil {
    const std::string &getJsonString (Object *object);

    int getJsonInt (Object *object);

    Object *getJsonObject (Object *object);

    void deleteJsonObject (Object *object);

    const std::vector<std::shared_ptr<Object >> &getJsonVec (Object *object);

    template<typename T>
    class getJsonVecByIndex {

    };

    template<>
    class getJsonVecByIndex<std::string> {
    public:
        std::string operator() (const std::vector<std::shared_ptr<Object >> &vec, int index) {
            auto l = vec.size();
            assert(l > index);
            auto elem = vec.at(index).get();
            std::string t;
            t = getJsonString(elem);
            return t;
        };
    };

    template<>
    class getJsonVecByIndex<int> {
    public:
        int operator() (const std::vector<std::shared_ptr<Object >> &vec, int index) {
            auto l = vec.size();
            assert(l > index);
            auto elem = vec.at(index).get();
            int t;
            t = getJsonInt(elem);
            return t;
        };
    };

    template<>
    class getJsonVecByIndex<Object *> {
    public:
        Object *operator() (const std::vector<std::shared_ptr<Object >> &vec, int index) {
            auto l = vec.size();
            assert(l > index);
            auto elem = vec.at(index).get();
            return elem;
        }
    };

};
#endif //HAPPYJSON_JSON_UTIL_H
