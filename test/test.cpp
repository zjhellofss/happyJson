//
// Created by fushenshen on 2020/1/3.
//

#include "../parse/parseJson.h"
#include "../util/jsonUtil.h"
#include <string>
#include <iostream>
#include <vector>
#include "../serialize/serializeJson.h"

int main () {
    using namespace std;
    Object *object = parseJson("{\n"
                               "  \"obj\": {\n"
                               "    \"name\": \"fss\"\n"
                               "  }\n"
                               "}");
//    Object *nameObject = object->getValue("aaa");
//    std::cout << JsonUtil::getJsonString(nameObject) << std::endl;

//    Object *plainVec = object->getValue("harr");
//    auto vec = JsonUtil::getJsonVec(plainVec);
//    auto item = JsonUtil::getJsonVecByIndex<double>()(vec, 0);
//    std::cout << item << std::endl;
    SerializeJson serializeJson;
    serializeJson.serializeObject(object);
    std::string str1 = serializeJson.getOutput();
    std::cout << str1 << std::endl;
    JsonUtil::deleteJsonObject(object);

    return 0;
}