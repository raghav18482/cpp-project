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
    cout<<"Please select what do you wanna do :"<<endl;
    line(10);
    getRow("1.","Donate");
    getRow("2.","Report");
    cin>>option;
    if(option==1){
        Donate d(c);
    }
    else if(option==2){
        Report r(c);
    }
}