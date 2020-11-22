#include<iostream>
#include<string>
#include<fstream>
#include"utility.h"
#include"storing.h"
#include"design.h"
#include<iomanip>
using namespace std;

class Customer{
    protected:
        string firstName;
        string lastName;
        int age;
        string gender;
        int count;
        string username;
        string password;
        int secretKey;
        string foldername;
        void getData();
        void displayDetails();
    public:
        Customer(){
            cout<<"Please enter your path : \n";
            cout<<"1. SignUp"<<endl<<"2. Singin"<<endl; 
            int option;
            cin>>option;
            if(option==1){
                signUp();
            }
            else{
                signin();
            }
        }

        void signUp();
        void signin();
};

void Customer::signUp(){
            cout<<"Enter your first Name: ";
            cin>>firstName;
            cout<<"Enter the last Name: ";
            cin>>lastName;
            cout<<"Age??";
            cin>>age;
            cout<<"Gender: ";
            cin>>gender;
            cout<<"Please create a username for yourself : ";
            cin>>username;
            while (true)
            {
                if(!checkUsername(username)){
                    break;
                }
                cout<<"This Username already exists please try another one : ";
                cin>>username;
            }
            
            cout<<"Please enter a secret key and remember it for future reference: ";
            cin>>secretKey;
            cout<<"Please enter a password : ";
            cin>>password;
            password=hashString(password,secretKey);
            makeFolder(username);
            foldername="data/"+username+"/";
            storeData(age,gender,firstName,lastName,foldername,password);
}

void Customer::signin(){
    cout<<"Please enter your username : ";
    cin>>username;
    while (true)
    {
        if(checkUsername(username)){
            break;
        }
        cout<<"You entered a wrong username"<<"please enter a valid username : ";
        cin>>username;
    }
    foldername="data/"+username+"/";
    cout<<"Please enter the secret key u entered with your password last time : ";
    cin>>secretKey;
    string passuser;
    cout<<"Please enter the password : ";
    cin>>passuser;
    password=passwordGrab(username);
    if(compareHashString(passuser,password,secretKey)){
        getData();
        displayDetails();
    }
    else{
        cout<<"Auth failed";
    }
    
}


void Customer::getData(){
    string url=foldername+"personal.txt";
    ifstream in;
    string temp;
    in.open(url.c_str());
    getline(in,firstName);
    getline(in,lastName);
    getline(in,gender);
    getline(in,temp);

}

void Customer::displayDetails(){
    curveLine(10);
    cout<<"Here Are your details"<<endl;
    line(10);
    cout<<"| "<<setw(15)<<"First Name "<<"| "<<setw(15)<<firstName<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Last Name "<<"| "<<setw(15)<<lastName<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Gender "<<"| "<<setw(15)<<gender<<" |";
    line(10);
}



class Donate:public Customer{
    int money;
    static int transactionId;
    public:
        Donate(){
            cout<<"Enter the money you want to donate : ";
        }

};

