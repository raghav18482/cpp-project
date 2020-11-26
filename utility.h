#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
using namespace std;
#pragma once

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
    for (int i = 0; i < comparator.length(); i++)
    {
        if (destination[i] != comparator[i] - key)
        {
            return false;
        }
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