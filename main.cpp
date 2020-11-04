#include<iostream>
#include<cstdio>
#include<fstream>
#include "storing.cpp"
using namespace std;

class Customer{
    protected:
        string firstName;
        string lastName;
        int age;
        char gender;
    public:
        Customer(){
            cout<<"Enter your first Name: ";
            cin>>firstName;
            cout<<"Enter the last Name: ";
            cin>>lastName;
            cout<<"Age??";
            cin>>age;
            cout<<"Gender(m/f): ";
            cin>>gender;
        }
};
class Donate:public Customer{
    protected:
        int money;
        int count;
    public:
        Donate(){
            cout<<"Enter the money you wanna donate ";
            cin>>money;
            string folderName=makeFolder(firstName,lastName,"donate");
            storeData(age,money,gender,folderName);
            count=getCount("donate");
            updateCount("donate",count+1);
        }
};
class Report:public Customer{

};
int main(){
    cout<<"Welcome to a pet NGO ";
    Donate d;
    return 0;
}