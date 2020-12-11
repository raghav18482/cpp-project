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
#include"design.h"
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
        string temp = "data/" + username + "/" + "p.txt";
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
void storeDataAdmin(string username,int age, string gender, string firstName, string lastName, string createdOn)
{
        string url = "data/admin/users.txt";
        ofstream out;
        out.open(url.c_str(),ios::app);
        out<<username<<endl;
        out << firstName << endl;
        out << lastName << endl;
        out << gender << endl;
        out << age << endl;
        out << createdOn << endl;
        out<<endl;
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
void storeDonationAdmin(string username,string timeOfDonation, int money, int transactionId)
{
        string url = "data/admin/donations.txt";
        ofstream out(url.c_str(),ios::app);
        out<<transactionId<<endl;
        out<<username<<endl;
        out << money << endl;
        out << timeOfDonation << endl;
        out<<endl;
        out.close();
}

void storeReport(string timeOfReport, string report, int reportId, string address, string type, string breed, string foldername)
{
        string url = foldername + "/" + to_string(reportId) + ".txt";
        ofstream out;
        out.open(url.c_str());
        out << report << endl;
        out << address << endl;
        out << timeOfReport << endl;
        out << type << endl;
        out << breed << endl;
        out.close();
}
void storeReportAdmin(string username,string timeOfReport, string report, int reportId, string address, string type, string breed)
{
        string url = "data/admin/reports.txt";
        ofstream out(url.c_str(),ios::app);
        out<<reportId<<endl;
        out<<username<<endl;
        out << report << endl;
        out << address << endl;
        out << timeOfReport << endl;
        out << type << endl;
        out << breed << endl;
        out<<endl;
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
void storeAdoptionAdmin(string username,string adoptionTime, string desc, int adoptionId, string type, string breed)
{
        string url = "data/admin/adoptions.txt";
        ofstream out;
        out.open(url.c_str(),ios::app);
        out<<adoptionId<<endl;
        out<<username<<endl;
        out << type << endl;
        out << desc << endl;
        out << breed << endl;
        out << adoptionTime << endl;
        out<<endl;
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
int getShowId()
{
        string url = "data/currentShowId.txt";
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


bool checkSlot(int slot,int numberOfTickets){
        int arr[4]={9,12,15,17};
        string temp=returnCurrentTime();
        int hour=getHour(temp);
        if(hour>arr[3]){
                cout<<"NGO is Closed"<<endl;
                return false;
        }
        if(hour>arr[slot-1]){
                cout<<"temp"<<endl;
                return false;
        }
        string url="data/show/"+to_string(slot)+".txt";
        ifstream in(url.c_str());
        if(in){
        getline(in,temp);
        in.close();
        if(conversionOfStringToInt(temp)<numberOfTickets){
                return false;
        }
        return true;
        }
        else{
                cout<<"Sorry server error "<<endl;
                return false;
        }

}

void storeTicket(struct Visitor *visitor,string username,int ticketId,string timeOfBooking,int numberOfBooking,string foldername,int slot){
        string url=foldername+"/"+to_string(ticketId)+".txt";
        ofstream out(url.c_str());
        out<<ticketId<<endl;
        out<<username<<endl;
        out<<numberOfBooking<<endl;
        out<<slot<<endl;
        out<<timeOfBooking<<endl;
        out<<endl;
        for (int i = 0; i < numberOfBooking; i++)
        {
                out<<visitor[i].name<<endl;
                out<<visitor[i].gender<<endl;
                out<<visitor[i].age<<endl;
                out<<endl;
        }

        out.close();
}


void updateSlotBooking(int slot,int numberOfTickets){
        auto url="data/show/"+to_string(slot)+".txt";
        ifstream in(url.c_str());
        string temp;
        getline(in,temp);
        in.close();
        ofstream out(url.c_str());
        out<<to_string(conversionOfStringToInt(temp)-numberOfTickets);
        out.close();
}


int getNumberOfBooking(int ticketId,string username){
        auto url="data/"+username+"/tickets/"+to_string(ticketId)+".txt";
        ifstream in(url.c_str());
        string temp;
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        return conversionOfStringToInt(temp);
}

struct Visitor* getVisitors(int ticketId,string username,int numberOfBooking,int *slot,string *timeOfBooking){
        auto url="data/"+username+"/tickets/"+to_string(ticketId)+".txt";
        struct Visitor*v=new Visitor[numberOfBooking];
        ifstream in(url.c_str());
        string temp;
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        *slot=conversionOfStringToInt(temp);
        getline(in,temp);
        *timeOfBooking=temp;
        getline(in,temp);
        for (int i = 0; i < numberOfBooking; i++)
        {
                getline(in,v[i].name);
                getline(in,v[i].gender);
                getline(in,temp);
                v[i].age=conversionOfStringToInt(temp);
                getline(in,temp);
        }

        return v;
        
}


void fetchAllDonations(){
        string url="data/admin/donations.txt";
        ifstream in(url.c_str());
        string temp;
        while (in)
        {
                getline(in,temp);
                if(temp!=""){
                getRow("id",temp);
                getline(in,temp);
                getRow("User",temp);
                getline(in,temp);
                getRow("money",temp);
                getline(in,temp);
                getRow("datetime",temp);
                getline(in,temp);
                temp="";
                }
        }
        
}

void fetchAllReports(){
        string url="data/admin/reports.txt";
        ifstream in(url.c_str());
        string temp;
        while (in)
        {
                getline(in,temp);
                if(temp!=""){
                getRow("id",temp);
                getline(in,temp);
                getRow("User",temp);
                getline(in,temp);
                getRow("report",temp);
                getline(in,temp);
                getRow("address",temp);
                getline(in,temp);
                getRow("datetime",temp);
                getline(in,temp);
                getRow("Type",temp);
                getline(in,temp);
                getRow("breed",temp);
                getline(in,temp);
                temp="";
                curveLine(5);
                }
        }
        
}
void fetchAllAdoptions(){
        string url="data/admin/adoptions.txt";
        ifstream in(url.c_str());
        string temp;
        while (in)
        {
                getline(in,temp);
                if(temp!=""){
                getRow("id",temp);
                getline(in,temp);
                getRow("User",temp);
                getline(in,temp);
                getRow("type",temp);
                getline(in,temp);
                getRow("desc",temp);
                getline(in,temp);
                getRow("datetime",temp);
                getline(in,temp);
                getRow("breed",temp);
                getline(in,temp);
                temp="";
                curveLine(5);
                }
        }
        
}

