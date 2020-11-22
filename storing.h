#include<iostream>
#include<cstdio>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<bits/stdc++.h>
#include<conio.h>
#include<unistd.h>
#include<sstream>
#include<string>
#include"utility.h"
using namespace std;
void makeFolder(string username){
        string foldername="data/"+username;
        mkdir(foldername.c_str());
}

bool checkUsername(string username){
        string temp="data/"+username+"/"+"personal.txt";
        ifstream in;
        in.open(temp.c_str());
        if(in)
        return true;
        else
        return false;
}

string passwordGrab(string username){
        string temp="data/"+username+"/"+"auth.txt";
        ifstream in;
        in.open(temp.c_str());
        string t;
        getline(in,t);
        in.close();
        return t;
}

void storeData(int age, string gender,string firstName,string lastName, string folderName,string password){
        string url=folderName+"personal.txt";
        ofstream out;
        out.open(url.c_str());
        out<<firstName<<endl;
        out<<lastName<<endl;
        out<<gender<<endl;
        out<<age<<endl;
        out.close();
        url=folderName+"p.txt";
        out.open(url.c_str());
        out<<password<<endl;
        out.close();
}

     



