#include<iostream>
#include<cstdio>
#include<fstream>

// #include"classes.h"
using namespace std;

int main(){
    
    ifstream in("test.txt");
    ofstream out("temp.txt");
    string line;
    while(getline(in,line)){
        if(line=="5"){
            getline(in,line);
            getline(in,line);
            getline(in,line);
            getline(in,line);
            getline(in,line);
            getline(in,line);
        }
        out<<line<<endl;
    }
    in.close();
    out.close();
    const char * p = "test.txt";
    remove(p);
    rename("temp.txt",p);    
    return 0;
}