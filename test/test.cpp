//
// Created by fushenshen on 2020/1/3.
//

#include "../parse/parseJson.h"
#include "../util/jsonUtil.h"
#include <string>
#include <iostream>
#include <vector>

int main () {
    using namespace std;
    Object *object = parseJson("{\n"
                               "  \"aaa\": \"fss\",\n"
                               "  \"obj\": {\n"
                               "    \"name\": \"fss\",\n"
                               "    \"age3\": 31,\n"
                               "    \"flag\": true,\n"
                               "    \"zzz\": [\n"
                               "      1,\n"
                               "      2,\n"
                               "      3,\n"
                               "      \"flla\"\n"
                               "    ]\n"
                               "  },\n"
                               "  \"harr\": [\n"
                               "    1,\n"
                               "    2,\n"
                               "    3,\n"
                               "    \"true\"\n"
                               "  ]\n"
                               "}");
    Object *nameObject = object->getValue("aaa");
    std::cout << JsonUtil::getJsonString(nameObject) << std::endl;

    Object *plainVec = object->getValue("harr");
    auto vec = JsonUtil::getJsonVec(plainVec);
    auto item = JsonUtil::getJsonVecByIndex<double >()(vec, 0);
    std::cout << item << std::endl;
    JsonUtil::deleteJsonObject(object);

    return 0;
}