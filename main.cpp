#include<iostream>
#include"classes.h"
using namespace std;
int main(){
	setTextColor(4);
    cout<<" Welcome to FirstJoy Pet NGO";
    curveLine(10);
    setTextColor(7);
    cout<<"Please enter your path : \n";
            cout<<"1. SignUp"<<endl<<"2. SignIn"<<endl; 
    int option;
    cin>>option;
    Customer c(option);
    cout<<"Please select what do you wanna do :"<<endl;
    line(5);
    getRow("1.","Donate");
    getRow("2.","Report");
    getRow("3.","Adopt");
    cin>>option;
    if(option==1){
        Donate d(c);
    }
    else if(option==2){
        Report r(c);
    }
    else if(option==3){
        Adoption a(c);
    }
}
