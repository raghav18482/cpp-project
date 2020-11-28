#include <iostream>
#include <cstdio>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <conio.h>
#include <unistd.h>
#include <string>
#include "utility.h"
using namespace std;
void makeFolder(string path)
{
        mkdir(path.c_str());
}

bool checkUsername(string username)
{
        string temp = "data/" + username + "/" + "personal.txt";
        ifstream in;
        in.open(temp.c_str());
        if (in)
                return true;
        else
                return false;
}

string passwordGrab(string username)
{
        string temp = "data/" + username + "/" + "auth.txt";
        ifstream in;
        in.open(temp.c_str());
        string t;
        getline(in, t);
        in.close();
        return t;
}

void storeData(int age, string gender, string firstName, string lastName, string folderName, string password, string createdOn)
{
        string url = folderName + "personal.txt";
        ofstream out;
        out.open(url.c_str());
        out << firstName << endl;
        out << lastName << endl;
        out << gender << endl;
        out << age << endl;
        out << createdOn << endl;
        out.close();
        url = folderName + "p.txt";
        out.open(url.c_str());
        out << password << endl;
        out.close();
}

void storeDonation(string timeOfDonation, int money, int transactionId, string foldername)
{
        string url = foldername + "/" + to_string(transactionId) + ".txt";
        ofstream out;
        out.open(url.c_str());
        out << money << endl;
        out << timeOfDonation << endl;
        out.close();
}

void storeReport(string timeOfDonation, string report, int reportId, string address, string type, string breed, string foldername)
{
        string url = foldername + "/" + to_string(reportId) + ".txt";
        ofstream out;
        out.open(url.c_str());
        out << report << endl;
        out << address << endl;
        out << timeOfDonation << endl;
        out << type << endl;
        out << breed << endl;
        out.close();
}

void storeAdoption(string adoptionTime, string desc, int adoptionId, string type, string breed, string foldername)
{
        string url = foldername + "/" + to_string(adoptionId) + ".txt";
        ofstream out;
        out.open(url.c_str());
        out << type << endl;
        out << desc << endl;
        out << breed << endl;
        out << adoptionTime << endl;
        out.close();
}

int getTransactionId()
{
        string url = "data/currentTransactionId.txt";
        string temp;
        int t;
        ifstream in;
        in.open(url.c_str());
        getline(in, temp);
        t = conversionOfStringToInt(temp);
        return t;
}
int getReportId()
{
        string url = "data/currentReportId.txt";
        string temp;
        int t;
        ifstream in;
        in.open(url.c_str());
        getline(in, temp);
        t = conversionOfStringToInt(temp);
        return t;
}

int getAdoptionId()
{
        string url = "data/currentAdoptionId.txt";
        string temp;
        int t;
        ifstream in;
        in.open(url.c_str());
        getline(in, temp);
        t = conversionOfStringToInt(temp);
        return t;
}

void updateId(int id, string action)
{
        string url = "data/" + action + ".txt";
        ofstream out;
        out.open(url.c_str());
        out << id << endl;
        out.close();
}

bool checkForPath(string path)
{
        ifstream in;
        in.open(path.c_str());
        if (in)
                return true;
        else
                return false;
}

void storePet(string type, string desc, string breed, string datetime, int reportId)
{
        string url = "data/pets/" + type + "s.txt";
        if (checkForPath(url))
        {
                ofstream out(url.c_str(), ios::app);
                out << endl;
                out << reportId << endl;
                out << breed << endl;
                out << desc << endl;
                out << datetime << endl;
                out << endl;
                out.close();
        }
        else
        {
                ofstream out(url.c_str(), ios::app);
                out << endl;
                out << endl;
                out << reportId << endl;
                out << breed << endl;
                out << desc << endl;
                out << datetime << endl;
                out << endl;
                out.close();
        }

        url = "data/pets/" + type + "scount.txt";
        int j = 0;
        string temp;
        if(checkForPath(url)){
                ifstream file(url.c_str());
                getline(file,temp);
                j=conversionOfStringToInt(temp);
                j++;
                file.close();
                ofstream out(url.c_str());
                out<<j;
                out.close();
        }
        else{
                ofstream out(url.c_str());
                out<<"1";
                out.close();
        }
}

void deleteItem(string id, string path)
{
        cout<<id<<endl;
        ifstream in(path.c_str());
        string p2 = "data/pets/temp.txt";
        ofstream out(p2.c_str());
        string line;
        while (getline(in, line))
        {
                if (line == id)
                {
                        getline(in, line);
                        getline(in, line);
                        getline(in, line);
                        getline(in, line);
                        getline(in, line);
                        getline(in, line);
                }
                out << line << endl;
        }
        in.close();
        out.close();
        remove(path.c_str());
        rename(p2.c_str(), path.c_str());
}




