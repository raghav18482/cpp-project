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
using namespace std;
#include "classes.cpp"

int getData(Customer *d){
    int money;
    ostringstream str1;
    str1<<d->count;
    string id=str1.str();
    ifstream in;
    string foldername="data/donate/"+id+"_"+d->firstName+d->lastName;
    string moneyFile=foldername+"/"+"money.txt";
    string ageFile=foldername+"/"+"age.txt";
    string genderFile=foldername+"/"+"gender.txt";
    in.open(moneyFile.c_str());
    in>>money;
    in.close();
    in.open(ageFile.c_str());
    in>>d->age;
    in.close();
    in.open(genderFile.c_str());
    in>>d->gender;
    in.close();
    return money;
}
