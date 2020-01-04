//
// Created by fushenshen on 2020/1/2.
//

#include <string>
#include <vector>

#include "serializeJson.h"
#include "../include/JsonObject.h"
#include "../util/jsonUtil.h"
#include "../exception/InvalidObjectException.h"

namespace JsonSerialize {
    inline void printPlainObject (const std::shared_ptr<Object> &elem) {
        std::cout << JsonUtil::getJsonString(elem.get());
    }

    inline void printArrObject (const std::string &name, const std::vector<std::shared_ptr<Object>> &vec) {
        std::cout << "[";
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            Type t = i->get()->getObjectType();
            if (t == Type::Integer) {
                printPlainObject(*i);
            } else if (t == Type::String) {
                printPlainObject(*i);
            }
            //todo
        }
    }

    void serializeJson (Object *object) {
        assert(object != nullptr);
        std::string str;
        auto m = object->getValues();
        int i = 0;
        for (const auto &elem:m) {
            i++;
            Type t = (elem.second)->getObjectType();
            std::cout << elem.first << ":";
            switch (t) {
                case Type::String: {
                    printPlainObject(elem.second);
                    break;
                }
                case Type::Integer: {
                    printPlainObject(elem.second);
                    break;
                }
                case Type::Array: {
                    break;
                }
                default:
                    throw InvalidObjectException("Unkown type");
            }

        }
        if (i != m.size()) {
            std::cout << ",";
        }
    }
}
