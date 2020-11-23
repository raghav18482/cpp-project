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
    cout<<"| "<<setw(15)<<"First Name "<<"| "<<setw(23)<<firstName<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Last Name "<<"| "<<setw(23)<<lastName<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Gender "<<"| "<<setw(23)<<gender<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Age "<<"| "<<setw(23)<<age<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Username "<<"| "<<setw(23)<<username<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Created On "<<"| "<<setw(23)<<createdOn<<" |";
    line(10);
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
        }
        void takeDonation();
        void displayDonationTicket();
        

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

void Donate::displayDonationTicket(){
    curveLine(10);
    cout<<"Here is your ticket please printout it :";
    line(10);
    cout<<"| "<<setw(15)<<"Transaction Id"<<" | "<<setw(23)<<transactionId<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Money donated"<<" | "<<setw(23)<<money<<" |";
    line(10);
    cout<<"| "<<setw(15)<<"Date Time"<<" | "<<setw(23)<<dateTime<<" |";
    line(10);
}

