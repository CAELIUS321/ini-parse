#include<iostream>
#include"IniFile.h"

using namespace std;
int main(){
    string filename="./config.ini";
    zhi::IniFile file;
    file.load(filename);
    file.show();
    file["MyApp"]["times"]=50;
    file["MyApp"]["value"]=12.0;
    file.save(filename);
    return 0;
}