cmake_minimum_required(VERSION 3.12)
project(happyJson2)

set(CMAKE_CXX_STANDARD 17)

add_executable(happyJson2  include/Object.h include/Integer.h include/Type.h test/test.cpp parse/parseJson.cpp parse/parseJson.h include/JsonObject.h exception/EmptyValueException.h exception/InvalidValueException.h include/String.h exception/InvalidStringException.h)