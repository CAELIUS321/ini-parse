/**
* @file IniFile.h
* @author caelius321
* @brief 一个用于解析和增删改查.ini文件的简单类库
**/
#include <string>
#include<map>
namespace zhi{
using namespace std;
class Value
{   

public:
    Value()=default;
    /**
     * @brief 
     * 可以传入(bool,int,double,char*,string)类型以构造Value对象
     * 
     */
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const char * value);
    Value(const string& value);
    /**
     * @brief 
     * 重载'='以将常见类型转换为Value&对象
     * @param (bool,int,double,char*,string) value 
     * @return Value&
     * @retval 传入数值对应的Value对象引用 
     */
    Value& operator=(bool value);
    Value& operator=(int value);
    Value& operator=(double value);
    Value& operator=(char * value);
    Value& operator=(const string& value);
    /**
     * @brief 
     * 将Value对象转换为bool\(int,double,string)
     * 
     * @return bool\(int,double,string)
     * @retval |Value对象的内容 |使用的函数      |返回值        |
     *         |---------------|---------------|-------------|
     *         |"true"         |bool()         |true         |
     *         |"false"        |bool()         |false        |
     *         |"n"(n为数值)    |int()或double()|n            | 
     *         |"这是一个字符串"|string()        |"这是一个字符串"|
     *  
     */
    operator bool();
    operator int();
    operator double();
    operator string();

    ~Value()=default;
private:
    string m_value;
};


typedef map<string, Value,less<>> Section;
class IniFile{
public:
    IniFile()=default;
    /**
     * @brief 
     * 
     * @param 加载的文件名 
     * @return true 加载成功
     * @return false 加载失败
     */
    bool load(const string& filename);
    /**
     * @brief 
     * 获取指定section的指定key的Value对象引用，推荐使用：
     * iniFile[section][key]
     * @param section 指定的段
     * @param key 指定的键
     * @return ** Value& 
     */
    Value& get(const string& section,const string& key);
    /**
     * @brief 
     * 使用：ini文件对象[段名]
     * using:iniFileObj[sectionName] 
     * @param section 段名称
     * @return ** Section& 段对象引用
     */
    Section& operator[](const string& section);
    /**
     * @brief 
     * 设置指定段和键的值，推荐使用另一种方式：
     * iniFileObj[section][key]=value
     * @param section 段名称
     * @param key 键名称
     * @param value Value对象，或者bool,int,double,string
     * @return ** void 
     */
    void set(const string& section,const string& key,const Value& value);
    /**
     * @brief 
     * 查询是否存在某个段
     * @param section 段名称
     * @return true 指定段存在
     * @return false 指定段不存在
     */
    bool has(const string& section);
    /**
     * @brief 
     * 查询指定段是否有某个键
     * @param section 段名称
     * @param key 键
     * @return true 指定段和键存在
     * @return false 段不存在或键不存在
     */
    bool has(const string& section,const string& key);
    /**
     * @brief 
     * 移除IniFile对象的一个Section
     * @param section 
     * @return ** void 
     */
    void remove(const string& section);
    /**
     * @brief 
     * 移除IniFile对象的一个Section中的指定Key-Value对
     * @param section 
     * @param key 
     * @return ** void 
     */
    void remove(const string& section,const string& key);
    /**
     * @brief 
     * 清除IniFile对象的内容
     * @return ** void 
     */
    void clear();
    /**
     * @brief 
     * 将IniFile对象的内容转换为.ini格式的字符串
     * @return ** string 
     */
    string to_string();
    /**
     * @brief 
     * 将IniFile对象的内容打印到终端
     * @return ** void 
     */
    void show();
    /**
     * @brief 
     * 将IniFile对象的内容保存到指定文件
     * @param filename 
     * @return true 保存成功
     * @return false 保存失败
     */
    bool save(const string& filename);
    ~IniFile()=default;
private:
    string m_filename;
    map<string,Section,less<>> m_sections;

};
namespace string_util{
    /**
     * @brief 
     * 去除字符串前后空格
     * @param str  
     * @return ** string 
     */
    string& trim(string& str);
}
}