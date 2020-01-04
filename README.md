# HappyJson
由C++11实现的支持嵌套的Json解析库

## HappyJson

* 将Json文件可以在内存中转化为Object形式的存在，存放于内存中的键值对以智能指针的形式存在，不需要过度关心内存泄漏的问题
* 通过向Object中添加对应的属性和值转化为Json字符串
## HappyJson库的使用方法

```C++
    //通过文件路径Json字符串并解析得到名为root的Object对象
    Object *root = readToken(readFile("test2.json"));
    
    Object *ageObject = root->getValue("age");
    //从root对象中得到Json对象中的int值
    JsonUtil::getJsonInt(ageObject) 
    
    Object *plainVec = root->getValue("ar2r");
    //从root对象中得到Json对象中的数组值
    auto vec = JsonUtil::getJsonVec(plainVec);
    //得到如上数组中的第i个值
    auto item = JsonUtil::getJsonVecByIndex<std::string>()(vec, 0);
    //释放资源
    JsonUtil::deleteJsonObject(object);

```


## 致谢

感谢CJson、RapidJson为我提供的灵感以及好朋友们提出的建议
