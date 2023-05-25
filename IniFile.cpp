#include"IniFile.h"
#include<fstream>
#include <sstream>
#include<iostream>
namespace zhi{

Value::Value(bool value){
    *this = value;
}

Value::Value(int value){
    *this = value;
}
Value:: Value(double value){
    *this = value;
}
Value::Value(const char * value){
    *this = value;
}
Value:: Value(const string& value){
    *this = value;
}

Value& Value::operator=(bool value){
    m_value=value?"true":"false";
    return *this;
}
Value& Value::operator=(int value){
    stringstream ss;
    ss<<value;
    m_value=ss.str();
    return *this;
}
Value& Value::operator=(double value){
    stringstream ss;
    ss<<value;
    m_value=ss.str();
    return *this;
}
Value& Value::operator=(char * value){
    stringstream ss;
    ss<<value;
    m_value=ss.str();
    return *this;
}
Value& Value::operator=(const string& value){
    m_value=value;
    return *this;
}

 Value::operator bool(){
    return m_value=="true";
 }
 Value::operator int(){
    return atoi(m_value.c_str());
 }
 Value::operator double(){
    return atof(m_value.c_str());
 }
 Value::operator string(){
    return m_value;
 }
bool IniFile::load(const string& filename){
    ifstream fin(filename);
    if(fin.fail())return false;
    string line,section;

    while(getline(fin,line)){
        if(line==""){
            continue;
        }
        if(line[0]=='['){
            int pos=line.find_first_of(']');
            section=trim(line.substr(1,pos-1));
            m_sections[section]=Section();
            continue;
        }
        int pos=line.find_first_of('=');
        string key=trim(line.substr(0,pos));
        string value=trim(line.substr(pos+1,line.length()-pos));
        m_sections[section][key]=value;
    }
    fin.close();
    return true;
}

Value& IniFile::get(const string& section,const string& key){
    return m_sections[section][key];
}
Section& IniFile::operator[](const string& section){
    return m_sections[section];
}

void IniFile::set(const string& section,const string& key,const Value& value){
    m_sections[section][key]=value;
}
bool IniFile::has(const string& section){
    return m_sections.find(section) != m_sections.end();
}

bool IniFile::has(const string& section,const string& key){
    auto it=m_sections.find(section);
    if(it==m_sections.end())return false;
    return it->second.find(key)!=it->second.end();
}
/*移除IniFile对象的一个Section*/
void IniFile::remove(const string& section){
    m_sections.erase(section);
}
/*移除IniFile对象的一个Section中的指定Key-Value对*/
void IniFile::remove(const string& section,const string& key){
    auto it=m_sections.find(section);
    if(it==m_sections.end())return;
    it->second.erase(key);
}
/*清除IniFile对象的内容*/
void IniFile::clear(){
    m_sections.clear();
}
/*
将IniFile对象的内容转换为.ini格式的字符串
*/
string IniFile::to_string(){
    stringstream ss;
    for(auto [first,second]:m_sections){
            ss<<"["<<first<<"]"<<endl;
        for(auto [key,value]:second){
                ss<<key<<" = "<<(string)value<<endl;
        }
        ss<<endl;
    }
    return ss.str();
}
/*
将IniFile对象的内容打印到终端
*/
void IniFile::show(){
    cout<<to_string();
}
/*
将IniFile对象的内容保存到指定文件
*/
bool IniFile::save(const string& filename){
    ofstream ofs(filename);
    if(ofs.fail()) return false;
    ofs<<to_string();
    ofs.close();
    return true;
}
/*
去除字符串前后空格
*/
string& trim(string& str){
    if(str.empty())return str;
    str.erase(0,str.find_first_not_of(" \n\r"));
    str.erase(str.find_last_not_of(" \n\r")+1);
    return str;
}

}