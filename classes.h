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
    friend class TicketCounter;
    Customer() {}
    //authentication choosing
    Customer(string username, int show = 1)
    {
        foldername = "data/" + username + "/";
        this->username = username;
        getData();
        if (show == 1)
        {
            displayDetails();
        }
    }
    Customer(int option)
    {
        checkDate();
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
    storeDataAdmin(username, age, gender, firstName, lastName, createdOn);
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
        cout << "Incorrect Credentials !!!!!  " << endl;
        setTextColor(7);
        signin();
    }
}

//fetching data from file into object
void Customer::getData()
{

    string url = foldername + "personal.txt";
    ifstream in;
    if (!in)
    {
        cout << "Cant open file" << endl;
    }
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
    Donate(Customer &c, int admin = 0, string tid = "null")
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
        if (admin == 1)
        {
            retrieveDonation(tid, 0);
            return;
        }
        makeFolder(foldername);
        choose();
    }
    void takeDonation();
    void displayDonationTicket();
    void retrieveDonation(string, int);
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
    storeDonationAdmin(username, dateTime, money, transactionId);
}

void Donate::retrieveDonation(string tid = "null", int takeId = 1)
{
    if (takeId == 1)
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
    }
    else
    {
        transactionId = conversionOfStringToInt(tid);
        foldername += "/" + tid + ".txt";
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
    transactionId = getTransactionId();
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
    void takeReport();
    void retrieveReport(string, int);
    void displayReportTicket();
    void choose();

public:
    Report() {}
    Report(Customer &c, int admin = 0, string tid = "null")
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
        if (admin == 1)
        {
            retrieveReport(tid, 0);
            return;
        }
        makeFolder(foldername);
        choose();
    }
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
    storeReportAdmin(username, dateTime, report, reportId, address, type, breed);
    updateId(reportId, "currentReportId");
    curveLine(8);
    cout << "Congrats Your Report has been recorded";
    line(5);
    displayReportTicket();
    storePet(type, report, breed, dateTime, reportId);
}

void Report::retrieveReport(string tid = "null", int takeId = 1)
{
    if (takeId == 1)
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
    }
    else
    {
        foldername += "/" + tid + ".txt";
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
    reportId=getReportId();
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
            id = to_string(temp);
            adoptionId = getAdoptionId();
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
        updateId(adoptionId, "currentAdoptionId");
        displayParticularPet();
        storeAdoption(adoptionTime, desc, adoptionId, type, breed, foldername);
        storeAdoptionAdmin(username, adoptionTime, desc, adoptionId, type, breed);
        ofstream o(urlForCount.c_str());
        j--;
        o << j;
        o.close();
        if (j == 0)
        {
            string urlTemp = "data/pets/" + type + "s.txt";
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

class TicketCounter : public Customer
{
protected:
    int ticketId;
    int numberOfBooking;
    int slot;
    string timeOfBooking;
    struct Visitor *visitor;
    void bookTickets();
    void retrieveTickets(int);

public:
    void displayTickets();
    TicketCounter(){};
    TicketCounter(int ticketId,string username){
        this->username=username;
        this->ticketId=ticketId;
        retrieveTickets(1);
    }
    TicketCounter(Customer c)
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
        foldername += "tickets";
        makeFolder(foldername);
        cout << "Welcome to our NGO's people fun with animals session" << endl;
        choose();
    }
    void choose();
};

void TicketCounter::choose()
{
    int option;
    cout << "1. Book a Ticket " << endl
         << "2. See Your Ticket" << endl;
    cin >> option;
    if (option == 1)
    {
        bookTickets();
    }
    else if (option == 2)
    {
        retrieveTickets(0);
    }
    else
    {
        cout << "Wrong Choice " << endl
             << "Enter again " << endl;
        choose();
    }
}

void TicketCounter::bookTickets()
{
    cout << "How Many Tickets Do you wanna book " << endl;
    cin >> numberOfBooking;
    cout << "Please select a slot :" << endl;
    line(5);
    getRow("No. ", "StartTime", "EndTime");
    getRow("1. ", "9:00am", "11:00am");
    getRow("2. ", "12:00pm", "2:00pm");
    getRow("3. ", "3:00pm", "5:00pm");
    getRow("4. ", "5:00am", "7:00pm");
    cin >> slot;
    if (checkSlot(slot, numberOfBooking))
    {
        visitor = new Visitor[numberOfBooking];
        for (int i = 0; i < numberOfBooking; i++)
        {
            visitor[i].getDetails(i);
        }
        timeOfBooking = returnCurrentTime();
        ticketId = getShowId();
        ticketId++;
        storeTicket(visitor, username, ticketId, timeOfBooking, numberOfBooking, foldername, slot);
        storeTicketAdmin(username,ticketId,timeOfBooking);
        updateId(ticketId, "currentShowId");
        updateSlotBooking(slot, numberOfBooking);
        displayTickets();
    }
    else
    {
        cout << "Sorry either slot is already done or full " << endl;
        choose();
    }
}
void TicketCounter::retrieveTickets(int admin=0)
{
    if(admin==0){
    int t;
    cout << "Please enter the ticket Id" << endl;
    cin >> t;
    if (!checkForPath(foldername + "/" + to_string(t) + ".txt"))
    {
        cout << "Wrong ticket id" << endl;
        choose();
        return;
    }
    ticketId = t;
    }
    numberOfBooking = getNumberOfBooking(ticketId, username);
    visitor = new Visitor[numberOfBooking];
    visitor = getVisitors(ticketId, username, numberOfBooking, &slot, &timeOfBooking);
    displayTickets();
}

void TicketCounter::displayTickets()
{
    string slotString[4] = {
        "9:00am-11:00am",
        "12:00pm-2:00pm",
        "3:00am-5:00pm",
        "5:00am-7:00am",
    };
    cout << "Here is your Tickets" << endl;
    line(5);
    getRow("Ticket Id", to_string(ticketId));
    sleep(2);
    getRow("Number of ticket", to_string(numberOfBooking));
    sleep(2);
    getRow("Booked By ", username);
    sleep(2);
    getRow("Booked On ", timeOfBooking);
    Sleep(2);
    getRow("Slot ", slotString[slot - 1]);
    Sleep(2);
    curveLine(5);
    getRow("Name", "Gender", "Age", 25, 15, 12);
    for (int i = 0; i < numberOfBooking; i++)
    {
        getRow(visitor[i].name, visitor[i].gender, to_string(visitor[i].age), 25, 15, 12);
        sleep(2);
    }

    curveLine(5);
}