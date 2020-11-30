#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
using namespace std;
#pragma once
string returnOriginalString(string,int);
string hashString(string destination, int key)
{
    char temp[destination.length()];
    for (int i = 0; i < destination.length(); i++)
    {
        temp[i] = destination[i] + key;
    }
    return temp;
}

bool compareHashString(string destination, string comparator, int key)
{
    if(returnOriginalString(comparator,key)!=destination){
        return false;
    }

    return true;
}

string returnOriginalString(string hashed, int key)
{
    string temp;
    for (int i = 0; i < hashed.length(); i++)
    {
        temp[i] = hashed[i] - key;
    }

    return temp;
}

int conversionOfStringToInt(string a)
{
    stringstream meow(a);
    int x = 0;
    meow >> x;
    return x;
}

string returnCurrentTime()
{
    auto timenow =
        chrono::system_clock::to_time_t(chrono::system_clock::now());
    string temp = ctime(&timenow);
    temp[temp.length() - 1] = '\0';
    return temp;
}

struct Visitor{
    string name;
    int age;
    string gender;

    void getDetails(int num){
        cout<<"Please enter the name of the "<<num+1<<" person : ";
        cin.ignore();
        getline(cin,name);
        cout<<"Please enter the age : ";
        cin>>age;
        cout<<"Please enter the gender ";
        cin>>gender;
    }

};