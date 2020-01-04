//
// Created by fushenshen on 2020/1/3.
//

#include "parseJson.h"
#include <string>
#include <fstream>
#include <cmath>
#include "../include/JsonObject.h"
#include "../exception/EmptyValueException.h"
#include "../exception/InvalidValueException.h"
#include "../exception/InvalidStringException.h"
#include "../include/String.h"


static std::string skipSpace (const std::string &json, int &pos) {
    auto p = json.data();
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
        p++;
    }
    return std::string(p);

}

/**
 * 解析NULL对象
 * @param json
 * @param pos
 * @return
 */
static bool parseNull (const std::string &json, int &pos) {
    assert(json[pos] == 'n');
    int len = static_cast<int>(json.size());
    if (pos + 3 > len) {
        return false;
    } else {
        bool f = json[pos + 1] == 'u' && json[pos + 2] == 'l' && json[pos + 3] == 'l';
        pos += 4;
        return f;
    }
}

/**
 * 解析Json对象中的true对象
 * @param json
 * @param pos
 * @return
 */
static bool parseTrue (const std::string &json, int &pos) {
    assert(json[pos] == 'n');
    int len = static_cast<int>(json.size());
    if (pos + 3 > len) {
        return false;
    } else {
        bool f = json[pos + 1] == 'r' && json[pos + 2] == 'u' && json[pos + 3] == 'e';
        pos += 4;
        return f;
    }
}

/**
 * 解析Json对象中的false对象
 * @param json
 * @param pos
 * @return
 */
static bool parseFalse (const std::string &json, int &pos) {
    assert(json[pos] == 'f');
    int len = static_cast<int>(json.size());
    if (pos + 4 > len) {
        return false;
    } else {
        bool f = json[pos + 1] == 'a' && json[pos + 2] == 'l'
                 && json[pos + 3] == 's' && json[pos + 4] == 'e';
        pos += 5;
        return f;
    }
}


static String *parseString (const std::string &json, int &pos) {
    assert(json[pos] == '"');
    auto p = json.begin();
    int l = static_cast<int>(json.size());
    pos++;//指向下一个位置
    int s1 = pos;
    String *strObject = nullptr;
    while (pos++ < l) {
        if (isalpha(json[pos])) {
            continue;
        } else if (json[pos] == '"') {
            std::string str = std::string(p + s1, p + pos );
            strObject = new String(str);
            return strObject;
        } else if (json[pos] == '\\') {
            assert(pos != l);
            switch (json[pos]) {
                case '\"':
                case '\\':
                case '/':
                case 'b':
                case 'f':
                case 'n':
                case 'r':
                case 't':
                    break;
                default:
                    throw InvalidValueException();

            }
        } else if (json[pos] == '\0') {
            throw InvalidStringException();
        } else if ((unsigned char) (json[pos] < 0x20)) {
            throw InvalidValueException();
        }
    }
    return strObject;
}

/**
 * 解析Json中的数字对象
 * @param json
 * @param pos
 * @return
 */
static Integer *parseNumber (const std::string &json, int &pos) {
    assert(isdigit(json[pos]));
    Integer *val = nullptr;
    bool isMinus = false;
    if (json[pos] == '-') {
        isMinus = true;
        pos++;
    } else if (json[pos] == '0') {
        while (json[pos] == '0') {
            pos++;
        }
    }
    int s = pos;
    //parse number
    if (!isdigit(json[pos])) {
        throw std::exception();
    } else {
        while (isdigit(json[pos])) {
            pos++;
        }
    }
    int s1 = pos;
    auto p = json.begin();
    //only number
    if (pos >= json.size()) {
        std::string numberStr = std::string(p + s, p + pos);
        double v = std::stod(numberStr);
        if (isMinus) {
            v = -v;
        }
        val = new Integer(v);
    } else {
        char c = json[pos];
        bool isExponent = false;
        if (c == '.' || c == 'E' || c == 'e') {
            if (c == 'e' || c == 'E') {
                isExponent = true;
            }
            pos++;
            int s2 = pos;
            while (pos < json.size()) {
                if (isdigit(json[pos])) {
                    pos++;
                } else {
                    throw InvalidValueException();
                }
            }
            double v;
            if (!isExponent) {
                v = std::stod(std::string(p + s, p + pos));
            } else {
                double v1 = std::stod(std::string(p + s, p + s1));
                double v2 = std::stod(std::string(p + s2, p + pos));
                v = v1 * std::pow(10, v2);
            }
            if (isMinus) {
                v = -v;
            }
            val = new Integer(v);
        } else {
            throw InvalidValueException();
        }
    }
    return val;
}

/**
 * 去除每部分Json中开头的空格
 * @param json
 * @param pos
 * @return
 */

//fixme 存在内存泄漏的情况
static Object *parseJson_ (std::string json, int &pos) {
    json = skipSpace(json, pos);
    Object *res = nullptr;
    bool f;
    switch (json[pos]) {
        case 'n': {
            f = parseNull(json, pos);
            if (f) {
                res = new Integer(-1);
                res->setObjectType(Type::Null);
            } else {
                //todo
            }
            break;
        }
        case 't': {
            f = parseTrue(json, pos);
            if (f) {
                res = new Integer(1);
                res->setObjectType(Type::Boolean);
            } else {
                //todo
            }
            break;
        }
        case 'f':
            f = parseFalse(json, pos);
            if (f) {
                res = new Integer(0);
                res->setObjectType(Type::Boolean);
            } else {
                //todo
            }
            break;
        case '"': {
            res = parseString(json, pos);
            break;
        }
        case '\0': {
            throw EmptyValueException();
        }
        default:
            res = parseNumber(json, pos);

            break;

    }

    return res;
}

Object *parseJson (const std::string &json) {
    int pos = 0;
    int len = static_cast<int>(json.size());
    parseJson_(json, pos);
    return 0;
}