#include<iostream>
#include"classes.h"
#include"admin.h"
using namespace std;
int main(){
	setTextColor(4);
    cout<<" Welcome to FirstJoy Pet NGO";
    curveLine(10);
    setTextColor(7);
    Customer *c;
    cout<<"Please enter your path : \n";
            cout<<"1. SignUp"<<endl<<"2. SignIn"<<endl<<"3. Admin"<<endl; 
    int option;
    cin>>option;
    if(option==1 || option==2)
    c=new Customer(option);
    else
    {
        Admin a;
        return 0;
    }
    
    cout<<"Please select what do you wanna do :"<<endl;
    line(5);
    getRow("1.","Donate");
    getRow("2.","Report");
    getRow("3.","Adopt");
    getRow("4.","Book Show");
    cin>>option;
    if(option==1){
        Donate d(*c);
    }
    else if(option==2){
        Report r(*c);
    }
    else if(option==3){
        Adoption a(*c);
    }
    else if(option==4){
        TicketCounter t(*c);
    }
}
