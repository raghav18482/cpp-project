#include<iostream>
#include<cstdio>
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
class Donate:public Customer{};
class Report:public Customer{};
int main(){
    cout<<"Welcome to a pet NGO ";
    return 0;
}