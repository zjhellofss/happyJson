#ifndef HAPPY_JSON_SERIALIZE_JSON_H
#define HAPPY_JSON_SERIALIZE_JSON_H

#include "../include/JsonObject.h"
#include "../util/jsonUtil.h"
#include "../exception/InvalidObjectException.h"
#include <string>
#include <sstream>
#include <iostream>

class SerializeJson {
public:
    SerializeJson () {

    }

    void serializeObject (Object *object) {
        output << "{";
        auto m = object->getValues();
        size_t i = 0;
        size_t count = m.size();
        output << object->getObjectName();
        for (const auto &p:m) {
            auto o = p.second.get();
            Type t = o->getObjectType();
            i++;
            switch (t) {
                case Type::Integer: {
                    auto integer = reinterpret_cast<Integer *>(o);
                    serializeNumber(integer);
                    break;
                }
                case Type::String: {
                    auto str = reinterpret_cast<String *>(o);
                    serializeString(str);
                    break;
                }
                case Type::Array: {
                    auto arr1 = reinterpret_cast<Array *>(o);
                    serializeArr(arr1);
                    break;
                }
                case Type::Boolean: {
                    auto b = reinterpret_cast<Integer *>(o);
                    serializeBoolean(b);
                    break;
                }
                case Type::Object: {
                    serializeObject(o);
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

    std::string getOutput () const {
        return output.str();
    }

private:
    void serializeString (String *str) {
        const std::string &name = str->getObjectName();
        const std::string &val = str->getStrVal();
        output << name << ":" << val;
    }

    void serializeNumber (Integer *integer) {
        const std::string &name = integer->getObjectName();
        const double val = integer->getVal();
        output << name << ":" << val;
    }

    void serializeBoolean (Integer *boolean) {
        const std::string &name = boolean->getObjectName();
        double v = boolean->getVal();
        if (v) {
            output << name << ":" << "true";
        } else {
            output << name << ":" << "false";
        }
    }

    void serializeArr (Array *arr) {
        auto vec = arr->getVec();
        output << "[";
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            auto o = i->get();
            Type t = o->getObjectType();
            switch (t) {
                case Type::Integer: {
                    auto integer = reinterpret_cast<Integer *>(o);
                    serializeNumber(integer);
                    break;
                }
                case Type::String: {
                    auto str = reinterpret_cast<String *>(o);
                    serializeString(str);
                    break;
                }
                case Type::Array: {
                    auto arr1 = reinterpret_cast<Array *>(o);
                    serializeArr(arr1);
                    break;
                }
                case Type::Boolean: {
                    auto b = reinterpret_cast<Integer *>(o);
                    serializeBoolean(b);
                    break;
                }
                case Type::Object: {
                    serializeObject(o);
                    break;
                }
                default: {
                    throw InvalidObjectException("Unknown object type");
                }
            }
            if (i != vec.end()) {
                output << ",";
            }
        }
        output << "]";
    }

private:
    std::stringstream output;
};


#endif //HAPPY_JSON_SERIALIZE_JSON_H
