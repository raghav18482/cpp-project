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
    friend class Adoption;
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
    cout << "Age?? ";
    cin >> age;
    cout << "Gender: ";
    cin >> gender;
    cout << "Please create a username for yourself: ";
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

    cout << "Please enter a secret number(0-10): ";
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
        cout << "You entered a wrong username "
             << "please enter a valid username : ";
        cin >> username;
    }
    foldername = "data/" + username + "/";
    cout << "Please enter your secret number : ";
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
        setTextColor(4);
        cout<<"Incorrect Credentials !!!!!  "<<endl;
        setTextColor(7);
        signin();
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
    curveLine(8);
    cout << "Here Are your details" << endl;
    line(5);
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
    curveLine(8);
    cout << "Congrats Your donation was successfull";
    line(5);
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
    line(5);
    curveLine(8);
    displayDonationTicket();
}

void Donate::choose()
{
    int option;
    setTextColor(6);
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
    curveLine(8);
    cout << "Here is your ticket please printout it :";
    line(5);
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
    string type;
    string breed;

public:
    Report() {}
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
    cout << "Please Write about the animal you are reporting about(like feautures color n all) : " << endl;
    cin.ignore();
    getline(cin, report);
    cout << "Please enter the address here where you find the animal : " << endl;
    getline(cin, address);
    cout << "Please enter the type of animal(eg. dog,cat) :" << endl;
    getline(cin, type);
    cout << "Please tell the breed of animal if you can " << endl;
    getline(cin, breed);
    dateTime = returnCurrentTime();
    reportId++;
    storeReport(dateTime, report, reportId, address, type, breed, foldername);
    updateId(reportId, "currentReportId");
    curveLine(8);
    cout << "Congrats Your Report has been recorded";
    line(5);
    displayReportTicket();
    storePet(type, report, breed, dateTime, reportId);
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

        cout << "Wrong Report id please enter again : ";
        cin >> t;
    }
    string temp;
    ifstream in;
    in.open(foldername.c_str());
    getline(in, report);
    getline(in, address);
    getline(in, dateTime);
    getline(in, type);
    getline(in, breed);
    in.close();
    line(5);
    curveLine(8);
    displayReportTicket();
}

void Report::displayReportTicket()
{
    curveLine(8);
    cout << "Here is your ticket please printout it :";
    line(5);
    getRow("Transaction Id", to_string(reportId));
    getRow("Your Report", report);
    getRow("Address ", address);
    getRow("Type", type);
    getRow("Breed", breed);
    getRow("Date Time", dateTime);
}

void Report::choose()
{
    int option;
    setTextColor(6);
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

class Adoption : public Customer
{

    string type;
    string id;
    string breed;
    string dateTime;
    string desc;
    string address;
    int adoptionId;
    string adoptionTime;

public:
    Adoption(){};
    Adoption(Customer &c)
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
        foldername += "adopted";
        makeFolder(foldername);
        cout << "Please Tell the animal you are looking for(eg. dog ,cat): " << endl;
        cin >> type;
        displayAll(type);
    }
    void displayAll(string);
    void choose(string);
    void displayParticularPet();
};

void Adoption::displayAll(string typeUser = "dog")
{
    string url = "data/pets/" + typeUser + "s.txt";
    string urlForCount = "data/pets/" + typeUser + "scount.txt";
    if (checkForPath(url))
    {
        string temp;
        int i = 0;
        ifstream no(urlForCount.c_str());
        getline(no, temp);
        no.close();
        int j = conversionOfStringToInt(temp);
        ifstream in(url.c_str());
        getline(in, temp);
        while (i < j)
        {
            getline(in, temp);
            getline(in, id);
            getline(in, breed);
            getline(in, desc);
            getline(in, dateTime);
            getline(in, temp);
            getRow("ID", id);
            getRow("Breed", breed);
            getRow("desc", desc);
            getRow("DateTime", dateTime);
            i++;
        }
        in.close();
        choose(typeUser);
    }
    else
    {
        cout << "Sorry we dont have those" << endl;
        cout << "Please Tell the animal you are looking for(eg. dog ,cat): " << endl;
        cin >> type;
        displayAll(type);
    }
}

void Adoption::choose(string typeUser = "dog")
{
    adoptionId = -1;
    int temp;
    string url = "data/pets/" + typeUser + "s.txt";
    string urlForCount = "data/pets/" + typeUser + "scount.txt";
    curveLine(7);
    cout << "Please select the id of the pet u wanna select" << endl;
    cin >> temp;
    string temp2;
    int i = 0;
    ifstream no(urlForCount.c_str());
    getline(no, temp2);
    no.close();
    int j = conversionOfStringToInt(temp2);
    ifstream in(url.c_str());
    getline(in, temp2);
    while (i < j)
    {
        getline(in, temp2);
        getline(in, id);
        getline(in, breed);
        getline(in, desc);
        getline(in, dateTime);
        getline(in, temp2);
        if (conversionOfStringToInt(id) == temp)
        {
            id =to_string(temp);
            adoptionId=getAdoptionId();
            adoptionId++;
            break;
        }
        i++;
    }
    in.close();

    if (adoptionId == -1)
    {
        cout << "Please select a valid id :";
        choose(typeUser);
    }
    else
    {
        adoptionTime = returnCurrentTime();
        updateId(adoptionId,"currentAdoptionId");
        displayParticularPet();
        storeAdoption(adoptionTime,desc,adoptionId,type,breed,foldername);
        ofstream o(urlForCount.c_str());
        j--;
        o<<j;
        o.close();
        if(j==0){
            string urlTemp="data/pets/"+type+"s.txt";
            remove(urlTemp.c_str());
        }
    }
}

void Adoption::displayParticularPet()
{
    cout << "Here is your pet " << endl;
    curveLine(7);
    cout << endl;
    line(8);
    getRow("Animal Id", id);
    getRow("Adoption Id", to_string(adoptionId));
    getRow("Breed", breed);
    getRow("desc", desc);
    getRow("Bring On", dateTime);
    getRow("AdoptedOn", adoptionTime);
    string path = "data/pets/" + type + "s.txt";
    deleteItem(id, path);
}