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

class Customer{
    protected:
        string firstName;
        string lastName;
        int age;
        char gender;
        int count;
    public:
    friend int getData(Customer *);
        Customer(){
            cout<<"Enter your first Name: ";
            cin>>firstName;
            cout<<"Enter the last Name: ";
            cin>>lastName;
            cout<<"Age??";
            cin>>age;
            cout<<"Gender(m/f): ";
            cin>>gender;
        }
        Customer(int id){
            count=id;
            cout<<"please enter first name and for verification\n";
            cin>>firstName;
            cout<<"last name"<<endl;
            cin>>lastName;
        }
};

