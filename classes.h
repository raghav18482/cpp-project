/*
1. This is the most important file in project it contains core classes used in program
2. A base class called customer is made with various fields representing its the feauture of the client
3. Customer class has authentication functions to authenticate a user
4. Donation and Report are classes derieved from Customer after the authentication is completed an object is derieved there
5. whole thing is stored in filing system 
*/


//standard libs
#include <iostream>
#include <string>
#include <fstream>

//custom header files for this project
#include "utility.h"
#include "storing.h"
#include "design.h"


using namespace std;
#pragma once



//base class
class Customer
{
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
    //making derived class as friends
    friend class Donate;
    friend class Report;
    Customer() {}
    //authentication choosing
    Customer(int option)
    {
        if (option == 1)
        {
            signUp();
        }
        else
        {
            signin();
        }
    }

    void signUp();
    void signin();
};


//signup for user
void Customer::signUp()
{
    cout << "Enter your first Name: ";
    cin >> firstName;
    cout << "Enter the last Name: ";
    cin >> lastName;
    cout << "Age??";
    cin >> age;
    cout << "Gender: ";
    cin >> gender;
    cout << "Please create a username for yourself : ";
    cin >> username;
    while (true)
    {
        if (!checkUsername(username))
        {
            break;
        }
        cout << "This Username already exists please try another one : ";
        cin >> username;
    }

    cout << "Please enter a secret key and remember it for future reference: ";
    cin >> secretKey;
    cout << "Please enter a password : ";
    cin >> password;

    //hashing the password
    password = hashString(password, secretKey);
    foldername = "data/" + username;
    makeFolder(foldername);
    foldername += "/";

    //the date datetime when user was created
    createdOn = returnCurrentTime();

    //storing in files
    storeData(age, gender, firstName, lastName, foldername, password, createdOn);
}


//signing in user
void Customer::signin()
{
    cout << "Please enter your username : ";
    cin >> username;
    while (true)
    {
        if (checkUsername(username))
        {
            break;
        }
        cout << "You entered a wrong username"
             << "please enter a valid username : ";
        cin >> username;
    }
    foldername = "data/" + username + "/";
    cout << "Please enter the secret key u entered with your password last time : ";
    cin >> secretKey;
    string passuser;
    cout << "Please enter the password : ";
    cin >> passuser;
    

    //grabing hashed password from file
    password = passwordGrab(username);

    //comparing the userinput and hashed password
    if (compareHashString(passuser, password, secretKey))
    {
        getData();
        displayDetails();
    }
    else
    {
        cout << "Auth failed";
    }
}


//fetching data from file into object
void Customer::getData()
{
    string url = foldername + "personal.txt";
    ifstream in;
    string temp;
    in.open(url.c_str());
    getline(in, firstName);
    getline(in, lastName);
    getline(in, gender);
    getline(in, temp);
    getline(in, createdOn);
    age = conversionOfStringToInt(temp);
}

void Customer::displayDetails()
{
    curveLine(10);
    cout << "Here Are your details" << endl;
    line(10);
    getRow("First Name", firstName);
    getRow("Last Name", lastName);
    getRow("Gender", gender);
    getRow("Age", to_string(age));
    getRow("Username", username);
    getRow("Created On", createdOn);
}

class Donate : public Customer
{
protected:
    int money;
    static int transactionId;
    string dateTime;

public:
    Donate() {}
    Donate(Customer &c)
    {
        this->firstName = c.firstName;
        this->lastName = c.lastName;
        this->age = c.age;
        this->gender = c.gender;
        this->secretKey = c.secretKey;
        this->foldername = c.foldername;
        this->username = c.username;
        this->password = c.password;
        this->createdOn = c.createdOn;
        foldername += "donation";
        makeFolder(foldername);
        choose();
    }
    void takeDonation();
    void displayDonationTicket();
    void retrieveDonation();
    void choose();
};

int Donate::transactionId = getTransactionId();

void Donate::takeDonation()
{
    cout << "Please enter the amount you wanna donate : " << endl;
    cin >> money;
    while (true)
    {
        if (money > 0)
        {
            break;
        }
        cout << "Please enter valid amount of money : ";
        cin >> money;
    }
    dateTime = returnCurrentTime();
    transactionId++;
    updateId(transactionId, "currentTransactionId");
    curveLine(10);
    cout << "Congrats Your donation was successfull";
    line(10);
    displayDonationTicket();
    storeDonation(dateTime, money, transactionId, foldername);
}

void Donate::retrieveDonation()
{
    cout << "Please Enter the Transaction id : ";
    int t;
    cin >> t;
    while (true)
    {
        if (checkForPath(foldername + "/" + to_string(t) + ".txt"))
        {
            transactionId = t;
            foldername += "/" + to_string(transactionId) + ".txt";
            break;
        }

        cout << "Wrong Transaction id please enter again : ";
        cin >> t;
    }
    string temp;
    ifstream in;
    in.open(foldername.c_str());
    getline(in, temp);
    getline(in, dateTime);
    money = conversionOfStringToInt(temp);
    in.close();
    line(10);
    curveLine(10);
    displayDonationTicket();
}

void Donate::choose()
{
    int option;
    setTextColor(5);
    cout << "Choose The Path : " << endl
         << "1. Donate" << endl
         << "2. See previous donation " << endl;
    setTextColor(7);
    cin >> option;
    while (true)
    {
        if (option == 1 || option == 2)
        {
            break;
        }
        setTextColor(4);
        cout << "Wrong Choose again : ";
        cin >> option;
    }
    setTextColor(7);
    if (option == 1)
        takeDonation();
    else
        retrieveDonation();
}

void Donate::displayDonationTicket()
{
    curveLine(10);
    cout << "Here is your ticket please printout it :";
    line(10);
    getRow("Transaction Id", to_string(transactionId));
    getRow("Money Donated", to_string(money));
    getRow("Date Time", dateTime);
}

class Report : public Customer
{
    static int reportId;
    string report;
    string address;
    string dateTime;

public:
    Report(Customer &c)
    {
        this->firstName = c.firstName;
        this->lastName = c.lastName;
        this->age = c.age;
        this->gender = c.gender;
        this->secretKey = c.secretKey;
        this->foldername = c.foldername;
        this->username = c.username;
        this->password = c.password;
        this->createdOn = c.createdOn;
        foldername += "reports";
        makeFolder(foldername);
        choose();
    }
    void takeReport();
    void retrieveReport();
    void displayReportTicket();
    void choose();
};

int Report::reportId = getReportId();

void Report::takeReport()
{
    cout << "Please Write about the animal you are reporting about : " << endl;
    cin.ignore();
    getline(cin, report);
    cout << "Please enter the address here where you find the animal : " << endl;
    getline(cin, address);
    dateTime = returnCurrentTime();
    reportId++;
    storeReport(dateTime, report, reportId, address, foldername);
    updateId(reportId, "currentReportId");
    curveLine(10);
    cout << "Congrats Your Report has been recorded";
    line(10);
    displayReportTicket();
}

void Report::retrieveReport()
{
    cout << "Please Enter the Report id : ";
    int t;
    cin >> t;
    while (true)
    {
        if (checkForPath(foldername + "/" + to_string(t) + ".txt"))
        {
            reportId = t;
            foldername += "/" + to_string(reportId) + ".txt";
            break;
        }

        cout << "Wrong Transaction id please enter again : ";
        cin >> t;
    }
    string temp;
    ifstream in;
    in.open(foldername.c_str());
    getline(in, report);
    getline(in, address);
    getline(in, dateTime);
    in.close();
    line(10);
    curveLine(10);
    displayReportTicket();
}

void Report::displayReportTicket()
{
    curveLine(10);
    cout << "Here is your ticket please printout it :";
    line(10);
    getRow("Transaction Id", to_string(reportId));
    getRow("Your Report", report);
    getRow("Address ", address);
    getRow("Date Time", dateTime);
}

void Report::choose()
{
    int option;
    setTextColor(5);
    cout << "Choose The Path : " << endl
         << "1. Report" << endl
         << "2. See previous Reports " << endl;
    setTextColor(7);
    cin >> option;
    while (true)
    {
        if (option == 1 || option == 2)
        {
            break;
        }
        setTextColor(4);
        cout << "Wrong Choose again : ";
        cin >> option;
    }
    setTextColor(7);
    if (option == 1)
        takeReport();
    else
        retrieveReport();
}
