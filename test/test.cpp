//
// Created by fushenshen on 2020/1/3.
//

#include "../parse/parseJson.h"
#include <string>
#include <iostream>

int main () {
    using namespace std;
    parseJson("\"hello\\tcpp\"");
    string str("hello\t");
    cout << str << endl;
}