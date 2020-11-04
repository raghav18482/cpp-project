#include<iostream>
#include<cstdio>
#include<fstream>
#include "storing.cpp"
using namespace std;

class Customer{
    protected:
        string firstName;
        string lastName;
        int age;
        char gender;
    public:
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
};
class Donate:public Customer{
    protected:
        int money;
    public:
        Donate(){
            cout<<"Enter the money you wanna donate ";
            cin>>money;
            makeFolder(firstName,lastName,"donate");
        }
};
class Report:public Customer{

};
int main(){
    cout<<"Welcome to a pet NGO ";
    Donate d;
    return 0;
}