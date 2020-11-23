#include<iostream>
#include"classes.h"
using namespace std;
int main(){
    cout<<"Welcome to meow meow PET NGO";
    curveLine(9);
    cout<<"Please enter your path : \n";
            cout<<"1. SignUp"<<endl<<"2. Singin"<<endl; 
    int option;
    cin>>option;
    Customer c(option);
    Donate d(c);
    d.takeDonation();
}