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
        this->serializeObject_("", object);
    }

    std::string getOutput () const {
        return output.str();
    }

private:

    void serializeObject_ (const std::string &name, Object *object);

    void serializeString (const std::string &name, String *str);

    void serializeNumber (const std::string &name, Integer *integer);

    void serializeBoolean (const std::string &name, Integer *boolean);


    void serializeArr (const std::string &name, Array *arr);

private:
    std::stringstream output;
};


#endif //HAPPY_JSON_SERIALIZE_JSON_H
