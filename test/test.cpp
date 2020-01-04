//
// Created by fushenshen on 2020/1/3.
//

#include "../parse/parseJson.h"
#include <string>
#include <iostream>
#include <vector>

int main () {
    using namespace std;
    parseJson("{\n"
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
              "  ],\n"
              "  \"name\": \"fss\"\n"
              "}");
    int i = 3;
    i++;
    return 0;
}