#include<iostream>
#include<string>
using namespace std;
#pragma once

string hashString(string destination,int key){
    char temp[destination.length()];
    for (int i = 0; i < destination.length(); i++)
    {
        temp[i]=destination[i]+key;
    }
    return temp;
}


bool compareHashString(string destination,string comparator,int key){
    for (int i = 0; i < comparator.length(); i++)
    {
        if(destination[i]!=comparator[i]-key){
            return false;
        }
    }

    return true;
}

string returnOriginalString(string hashed,int key){
    string temp;
    for (int i = 0; i < hashed.length(); i++)
    {
        temp[i]=hashed[i]-key;
    }

    return temp;
    
}