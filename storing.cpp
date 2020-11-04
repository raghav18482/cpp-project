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
string makeFolder(string firstName, string lastName, string action){
        string foldername="data/"+action+"/"+firstName+lastName;
        mkdir(foldername.c_str());
        return foldername;
}

void storeData(int age, int money, char gender, string folderName){
        string moneyFile=folderName+"/"+"money.txt";
        string ageFile=folderName+"/"+"age.txt";
        string genderFile=folderName+"/"+"gender.txt";
        ofstream out;
        out.open(moneyFile.c_str());
        out<<money;
        out.close();
        out.open(ageFile.c_str());
        out<<age;
        out.close();
        out.open(genderFile.c_str());
        out<<gender;
        out.close();
}

int getCount(string action){
        string foldername="data/"+action+"/"+"count.txt";
        ifstream fin;
        fin.open(foldername.c_str());
        int count;
        string line;
        while (fin)
        {
                getline(fin,line);
        }
        fin.close();
        stringstream geek(line); 
        geek>>count;
        return count;
}


void updateCount(string action, int count){
        string foldername="data/"+action+"/"+"count.txt";
        // string counting=to_string(count);
        ofstream out;
        out.open(foldername.c_str());
        out<<count;
        out.close();     
}       



