#include"classes.h"
#pragma once


class Admin{
    string username;
    string password;
    void login();
    void options();
    void displayPersonByName(string name);
    void displayDonationsByUser(string username);
    void displayReportsByUser(string username);
    public:
    Admin(){
        cout<<"You have reached admin panel please enter the username and password "<<endl;
        login();
    }
};


void Admin::login(){
    cout<<"Username ";
    cin>>username;
    if(username!="meow"){
        setTextColor(4);
        cout<<"Incorrect username !!!"<<endl;
        setTextColor(7);
        return login();
    }
    cout<<"Password : ";
    cin>>password;
    if(password!="meow123"){
        setTextColor(4);
        cout<<"Incorrect Password !!!"<<endl;
        setTextColor(7);
        return login();
    }
    options();

}


void Admin::options(){
    cout<<"What do u wanna do?? sir??"<<endl;
    int option;
    curveLine(5);
    getRow("1.","All donations");
    getRow("2.","All Reports");
    getRow("3.","All Pets");
    getRow("4.","Search person");
    getRow("5.","All Shows tickets for Today");
    getRow("6.","Donations by username");
    cin>>option;
    string temp;
    switch (option)
    {
    case 1:
        fetchAllDonations();
        break;
    case 2:
        fetchAllReports();
        break;
    case 3:
        fetchAllAdoptions();
        break;
    case 4:
        cout<<"Enter the name u wanna search";
        cin>>temp;
        displayPersonByName(temp);
        break;
    case 5:
        fetchAllDonations();
        break;
    case 6:
        cout<<"Enter the username u wanna search";
        cin>>temp;
        displayDonationsByUser(temp);
    
    default:
        break;
    }
}


void Admin::displayPersonByName(string name){
    string tempUser;
    string temp;
    string url="data/admin/users.txt";
    ifstream in(url.c_str());
    while (in)
    {
        getline(in,tempUser);
        getline(in,temp);
        if(temp==name){
            Customer *c=new Customer(tempUser); 
            return;
        }
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        temp="";
    }
    in.close();

    cout<<"sorry not found"<<endl;
    
}


void Admin::displayDonationsByUser(string username){
    string tempId;
    string temp;
    string url="data/admin/donations.txt";
    ifstream in(url.c_str());
    while (in)
    {
        getline(in,tempId);
        getline(in,temp);
        if(temp==username){
            Customer *c=new Customer(username,0);
            Donate *d=new Donate(*c,1,tempId);
            delete c;
            delete d;
        }
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        temp="";
    }

    in.close();
    
}


void Admin::displayReportsByUser(string username){
    string tempId;
    string temp;
    string url="data/admin/reports.txt";
    ifstream in(url.c_str());
    while (in)
    {
        getline(in,tempId);
        getline(in,temp);
        if(temp==username){
            Customer *c=new Customer(username,0);
            Report *r=new Report(*c,1,tempId);
            delete c;
            delete d;
        }
        getline(in,temp);
        getline(in,temp);
        getline(in,temp);
        temp="";
    }
}





