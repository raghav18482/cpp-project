#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include<fstream>
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
        cout<<returnOriginalString<<destination<<endl;
        return false;
    }

    return true;
}

string returnOriginalString(string hashed, int key)
{
    string temp="";
    cout<<hashed<<endl;
    for (int i = 0; i < hashed.length(); i++)
    {
        temp+=  hashed[i] - key;
        cout<<temp<<endl;
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

    void showDetails(){
        cout<<name<<age<<gender<<endl;
    }

};

int getHour(string t){
    string temp;
    int space=0;
    for (int i = 0; i < t.length(); i++)
    {
        if(space==3){
            temp+=t[i];
            temp+=t[i+1];
            break;
        }
        if(t[i]==' '){
            space++;
        }
    }
    return conversionOfStringToInt(temp);
}

int getDate(ifstream &in){
    string temp;
    in>>temp;
    in>>temp;
    in>>temp;
    return conversionOfStringToInt(temp);
}


int getDate(string dt){
    int temp=0;
    string temp2="";
    for (int i = 0; i < dt.length(); i++)
    {
        if(temp==2){
            temp2+=dt[i];
            temp2+=dt[i+1];
            break;
        }
        if(dt[i]==' '){
            temp++;
        }
    }
    
    return conversionOfStringToInt(temp2);
}

void checkDate(){
    ifstream in("data/show/date.txt");
    int fileDate=getDate(in);
    in.close();
    int realDate=getDate(returnCurrentTime());
    if(fileDate!=realDate){
        ofstream out("data/show/date.txt");
        out<<returnCurrentTime();
        out.close();
        string url="data/show/";
        for (int i = 0; i < 4; i++)
        {
            url+=to_string(i+1)+".txt";
            out.open(url.c_str());
            out<<50;
            out.close();
            url="data/show/";
        }
    }
    return ;
}


string getDateMonthyear(){
    string date=returnCurrentTime();
    string temp="";
    for (int i = 0; i < date.length(); i++)
    {
        if(i<=10 || i>=20){
            temp+=date[i];
        }
    }
    return temp;
    
}