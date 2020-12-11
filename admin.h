#include"classes.h"
#pragma once


class Admin{
    string username;
    string password;
    void login();
    void options();
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
    getRow("4.","All Adoptions");
    getRow("5.","All Shows tickets for Today");
    cin>>option;
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
        fetchAllAdoptions();
        break;
    case 5:
        fetchAllDonations();
        break;
    
    default:
        break;
    }
}