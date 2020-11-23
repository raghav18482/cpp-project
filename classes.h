#include<iostream>
#include<string>
#include<fstream>
#include"utility.h"
#include"storing.h"
#include"design.h"
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
        string createdOn;
        void getData();
    public:
    void displayDetails();
    friend class Donate;
        Customer(){}
        Customer(int option){
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
            foldername="data/"+username;
            makeFolder(foldername);
            foldername+="/";
            createdOn=returnCurrentTime();
            storeData(age,gender,firstName,lastName,foldername,password,createdOn);
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
    getline(in,createdOn);
    age=conversionOfStringToInt(temp);

}

void Customer::displayDetails(){
    curveLine(10);
    cout<<"Here Are your details"<<endl;
    line(10);
    getRow("First Name",firstName);
    getRow("Last Name",lastName);
    getRow("Gender",gender);
    getRow("Age",to_string(age));
    getRow("Username",username);
    getRow("Created On",createdOn);
}



class Donate:public Customer{
    protected:
    int money;
    static int transactionId;
    string dateTime;
    public:
        Donate(){}

        Donate(Customer &c){
            this->firstName=c.firstName;
            this->lastName=c.lastName;
            this->age=c.age;
            this->gender=c.gender;
            this->secretKey=c.secretKey;
            this->foldername=c.foldername;
            this->username=c.username;
            this->password=c.password;
            this->createdOn=c.createdOn;
            foldername+="donation";
            makeFolder(foldername);
            choose();
        }
        void takeDonation();
        void displayDonationTicket();
        void retrieveDonation();
        void choose();
};

int Donate::transactionId=getTransactionId();

void Donate::takeDonation(){
    cout<<"Please enter the amount you wanna donate : "<<endl;
    cin>>money;
    while (true)
    {
        if(money>0){
            break;
        }
        cout<<"Please enter valid amount of money : ";
        cin>>money;
    }
    dateTime=returnCurrentTime();
    cout<<dateTime;
    transactionId++;
    updateTransactionId(transactionId);
    curveLine(10);
    cout<<"Congrats Your donation was successfull";
    line(10);
    displayDonationTicket();
    storeDonation(dateTime,money,transactionId,foldername);
}

void Donate::retrieveDonation(){
    cout<<"Please Enter the Transaction id : ";
    int t;
    cin>>t;
    while (true)
    {
        if(checkForPath(foldername+"/"+to_string(t)+".txt")){
            transactionId=t;
            foldername+="/"+to_string(transactionId)+".txt";
            break;
        }

        cout<<"Wrong Transaction id please enter again : ";
        cin>>t;
    }
    string temp;
    ifstream in;
    in.open(foldername.c_str());
    getline(in,temp);
    getline(in,dateTime);
    money=conversionOfStringToInt(temp);
    in.close();
    line(10);
    curveLine(10);
    displayDonationTicket();
}

void Donate::choose(){
    int option;
    setTextColor(5);
    cout<<"Choose The Path : "<<endl<<"1. Donate"<<endl<<"2. See previous donation "<<endl;
    setTextColor(7);
    cin>>option;
    while (true)
    {
        if(option==1 || option==2){
            break;
        }
        setTextColor(4);
        cout<<"Wrong Choose again : ";
        cin>>option;
    }
    setTextColor(7);
    if(option==1)takeDonation();
    else retrieveDonation();
}

void Donate::displayDonationTicket(){
    curveLine(10);
    cout<<"Here is your ticket please printout it :";
    line(10);
    getRow("Transaction Id",to_string(transactionId));
    getRow("Money Donated",to_string(money));
    getRow("Date Time",dateTime);
}



