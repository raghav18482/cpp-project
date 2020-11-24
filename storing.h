#include<iostream>
#include<cstdio>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<bits/stdc++.h>
#include<conio.h>
#include<unistd.h>
#include<string>
#include"utility.h"
using namespace std;
void makeFolder(string path){
        mkdir(path.c_str());
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

void storeData(int age, string gender,string firstName,string lastName, string folderName,string password,string createdOn){
        string url=folderName+"personal.txt";
        ofstream out;
        out.open(url.c_str());
        out<<firstName<<endl;
        out<<lastName<<endl;
        out<<gender<<endl;
        out<<age<<endl;
        out<<createdOn<<endl;
        out.close();
        url=folderName+"p.txt";
        out.open(url.c_str());
        out<<password<<endl;
        out.close();
}


void storeDonation(string timeOfDonation,int money, int transactionId,string foldername){
        string url=foldername+"/"+to_string(transactionId)+".txt";
        ofstream out;
        out.open(url.c_str());
        out<<money<<endl;
        out<<timeOfDonation<<endl;
        out.close();
}

void storeReport(string timeOfDonation,string report, int reportId,string address,string foldername){
        string url=foldername+"/"+to_string(reportId)+".txt";
        ofstream out;
        out.open(url.c_str());
        out<<report<<endl;
        out<<address<<endl;
        out<<timeOfDonation<<endl;
        out.close();
}


int getTransactionId(){
        string url="data/currentTransactionId.txt";
        string temp;
        int t;
        ifstream in;
        in.open(url.c_str());
        getline(in,temp);
        t=conversionOfStringToInt(temp);
        return t;
}
int getReportId(){
        string url="data/currentReportId.txt";
        string temp;
        int t;
        ifstream in;
        in.open(url.c_str());
        getline(in,temp);
        t=conversionOfStringToInt(temp);
        return t;
}

void updateId(int id,string action){
        string url="data/"+action+".txt";
        ofstream out;
        out.open(url.c_str());
        out<<id<<endl;
        out.close();
}



bool checkForPath(string path){
        ifstream in;
        in.open(path.c_str());
        if(in)
        return true;
        else
        return false;
}


     



