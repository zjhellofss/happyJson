//
// Created by fushenshen on 2020/1/3.
//

#include "parseJson.h"
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

#include "../include/JsonObject.h"
#include "../include/String.h"
#include "../include/Array.h"

#include "../exception/EmptyValueException.h"
#include "../exception/InvalidValueException.h"
#include "../exception/InvalidStringException.h"
#include "../exception/InvalidArrException.h"
#include "../exception/InvalidObjectException.h"


static void skipSpace (const std::string &json, int &pos) {
    auto p = json.data() + pos;
    auto p1 = p;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
        p++;
    }
    pos += p - p1;
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
    assert(json[pos] == 't');
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
    String *strObject = nullptr;
    assert(json[pos] == '"');
    const char *p = json.data() + pos;
    auto p1 = p;
    p++;
    std::vector<char> stk;
    while (*p != '\0') {
        char ch = *p++;
        if (isalpha(ch)) {
            stk.push_back(ch);
        } else if (ch == '\\') {
            switch (*p) {
                case '\"': {
                    stk.push_back('"');
                    break;
                }
                case '\\': {
                    stk.push_back('\\');
                    break;
                }
                case '/': {
                    stk.push_back('/');
                    break;
                }
                case 'b': {
                    stk.push_back('\b');
                    break;
                }
                case 'f': {
                    stk.push_back('\f');
                    break;
                }
                case 'n': {
                    stk.push_back('\n');
                    break;
                }
                case 'r': {
                    stk.push_back('\r');
                    break;
                }

                case 't': {
                    stk.push_back('\t');
                    break;
                }
                default: {
                    throw InvalidStringException("Invalid character");
                }
            }
            p++;
        } else if (ch == '"') {
            strObject = new String(stk.data());
            break;
        } else if (ch == '\0') {
            throw InvalidStringException("Miss invalid quotation mark");
        } else {
            //处理其他的字符
            if ((unsigned char) ch < 0x20) {
                throw InvalidStringException("Invalid character");

            }
        }
    }
    pos += p - p1;
    return strObject;
}


static Array *parseArray (const std::string &json, int &pos);

static Integer *parseNumber (const std::string &json, int &pos);

static Object *parseObject (const std::string &json, int &pos);

//fixme 存在内存泄漏的情况
static Object *parseJson_ (std::string json, int &pos) {
    skipSpace(json, pos);
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
        case '[': {
            res = parseArray(json, pos);
            break;
        }
        case '{': {
            res = parseObject(json, pos);
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


static Object *parseObject (const std::string &json, int &pos) {
    assert(json[pos] == '{');
    pos++;
    Object *obj = nullptr;
    skipSpace(json, pos);
    if (json[pos] == '}') {
        obj = new Object("", Type::Object);
    } else {
        if (json[pos] != '"') {
            throw InvalidObjectException("Invalid object");
        } else {
            obj = new Object("", Type::Object);
            while (true) {
                std::string name(parseString(json, pos)->getStrVal());
                skipSpace(json, pos);
                if (json[pos] == ':') {
                    pos++;
                } else {
                    delete obj;
                    obj = nullptr;
                    throw InvalidObjectException("Invalid object");
                }
                skipSpace(json, pos);
                //读取键值对的值
                Object *childObj = parseJson_(json, pos);
                obj->setValue(name, childObj);
                skipSpace(json, pos);
                char c = json[pos];
                if (c == ',') {
                    pos++;
                    skipSpace(json, pos);
                } else if (c == '}') {
                    pos++;
                    break;
                } else {
                    delete obj;
                    obj = nullptr;
                    throw InvalidObjectException("Invalid object");
                }
            }

        }
    }
    return obj;
}


static Array *parseArray (const std::string &json, int &pos) {
    assert(json[pos] == '[');
    pos++;
    int len = static_cast<int>(json.size());
    Array *arr = nullptr;
    //消去开头空格的部分
    skipSpace(json, pos);
    if (pos + 1 < len && json[pos + 1] == ']') {
        arr = new Array();
    } else {
        arr = new Array();
        while (true) {
            Object *obj = parseJson_(json, pos);
            arr->push(obj);
            skipSpace(json, pos);
            assert(pos < len);
            if (json[pos] == ',') {
                pos++;
                skipSpace(json, pos);
            } else if (json[pos] == ']') {
                pos++;
                break;
            } else {
                delete arr;
                arr = nullptr;
                throw InvalidArrException("Invalid Array elements");
            }
        }
    }

    return arr;
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
    if (json[pos] != '.' && json[pos] != 'E' && json[pos] != 'e') {
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
                    throw InvalidValueException("Invalid number");
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
            throw InvalidValueException("Invalid character in number");
        }
    }
    return val;
}


Object *parseJson (const std::string &json) {
    int pos = 0;
    skipSpace(json, pos);
    pos++;//skip '{'
    skipSpace(json, pos);
    int len = static_cast<int>(json.size());
    Object *root = new Object("", Type::Object);
    while (pos < len) {
        skipSpace(json, pos);
        if (json[pos] == '}') {
            break;
        }
        std::string name(parseString(json, pos)->getStrVal());
        skipSpace(json, pos);
        if (json[pos] == ':') {
            pos++;
        } else {
            throw InvalidObjectException("Invalid Object");
        }
        Object *res = parseJson_(json, pos);
        root->setValue(name, res);
        skipSpace(json, pos);
        if (json[pos] == ',') {
            pos++;
        }
        skipSpace(json, pos);

    }
    return root;
}

