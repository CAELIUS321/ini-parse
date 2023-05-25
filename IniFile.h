#include <string>
#include<map>
namespace zhi{
using namespace std;
class Value
{   

public:
    Value()=default;
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const char * value);
    Value(const string& value);

    Value& operator=(bool value);
    Value& operator=(int value);
    Value& operator=(double value);
    Value& operator=(char * value);
    Value& operator=(const string& value);

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
    bool load(const string& filename);
    Value& get(const string& section,const string& key);
    Section& operator[](const string& section);
    void set(const string& section,const string& key,const Value& value);
    bool has(const string& section);
    bool has(const string& section,const string& key);
    void remove(const string& section);
    void remove(const string& section,const string& key);
    void clear();
    string to_string();
    void show();
    bool save(const string& filename);
    ~IniFile()=default;
private:
    string m_filename;
    map<string,Section,less<>> m_sections;

};

string trim(const string& str); 
}