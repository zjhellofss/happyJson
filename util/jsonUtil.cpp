//
// Created by fushenshen on 2019/12/31.
//

#include "json_util.h"


namespace JsonUtil {
    const std::string &getJsonString (Object *object) {
        assert(object != nullptr);
        assert(object->getObjectType() == Type::String);
        auto *str = reinterpret_cast<String *>(object);
        return str->getStrVal();
    }

    int getJsonInt (Object *object) {
        assert(object != nullptr);
        assert(object->getObjectType() == Type::Integer);
        auto *integer = reinterpret_cast<Integer *>(object);
        return integer->getIntVal();
    }

    Object *getJsonObject (Object *object) {
        assert(object != nullptr);
        assert(object->getObjectType() == Type::Object);
        return object;
    }

    const std::vector<std::shared_ptr<Object >> &getJsonVec (Object *object) {
        assert(object != nullptr);
        assert(object->getObjectType() == Type::Array);
        auto *vec = reinterpret_cast<Array *> (object);
        return vec->getVec();
    }


    void deleteJsonObject (Object *object) {
        assert(object != nullptr);
        delete object;
    }

};
