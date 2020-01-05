//
// Created by fushenshen on 2020/1/2.
//

#include "serializeJson.h"

void SerializeJson::serializeObject_ (const std::string &name, Object *object) {
    if (!name.empty()) {
        output << name << ":";
    }
    output << "{";
    auto m = object->getValues();
    size_t i = 0;
    size_t count = m.size();
    for (const auto &p:m) {
        auto o = p.second.get();
        Type t = o->getObjectType();
        i++;
        switch (t) {
            case Type::Integer: {
                auto integer = reinterpret_cast<Integer *>(o);
                serializeNumber(p.first, integer);
                break;
            }
            case Type::String: {
                auto str = reinterpret_cast<String *>(o);
                serializeString(p.first, str);
                break;
            }
            case Type::Array: {
                auto arr1 = reinterpret_cast<Array *>(o);
                serializeArr(p.first, arr1);
                break;
            }
            case Type::Boolean: {
                auto b = reinterpret_cast<Integer *>(o);
                serializeBoolean(p.first, b);
                break;
            }
            case Type::Object: {
                serializeObject_(p.first, o);
                break;
            }
            default: {
                throw InvalidObjectException("Unknown object type");
            }
        }
        if (i != count) {
            output << ",";
        }
    }
    output << "}";
}

void SerializeJson::serializeString (const std::string &name, String *str) {
    if (!name.empty()) {
        output << name << ":";
    }
    const std::string &val = str->getStrVal();
    output << val;
}

void SerializeJson::serializeNumber (const std::string &name, Integer *integer) {
    if (!name.empty()) {
        output << name << ":";
    }
    const double val = integer->getVal();
    output << val;
}

void SerializeJson::serializeBoolean (const std::string &name, Integer *boolean) {
    double v = boolean->getVal();
    if (!name.empty()) {
        output << name << ":";
    }
    if (v == 1) {
        output << "true";
    } else {
        output << "false";
    }
}

void SerializeJson::serializeArr (const std::string &name, Array *arr) {
    auto vec = arr->getVec();
    if (name != "") {
        output << name << ":";
    }
    output << "[";
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        auto o = i->get();
        Type t = o->getObjectType();
        switch (t) {
            case Type::Integer: {
                auto integer = reinterpret_cast<Integer *>(o);
                serializeNumber("", integer);
                break;
            }
            case Type::String: {
                auto str = reinterpret_cast<String *>(o);
                serializeString("", str);
                break;
            }
            case Type::Array: {
                auto arr1 = reinterpret_cast<Array *>(o);
                serializeArr("", arr1);
                break;
            }
            case Type::Boolean: {
                auto b = reinterpret_cast<Integer *>(o);
                serializeBoolean("", b);
                break;
            }
            case Type::Object: {
                serializeObject_("", o);
                break;
            }
            default: {
                throw InvalidObjectException("Unknown object type");
            }
        }
        if (vec.end() - i > 1) {
            output << ",";
        }
    }
    output << "]";
}