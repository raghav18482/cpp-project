#include<iostream>
#include<cstdio>
#include<fstream>
#include "storing.cpp"
#include "extract.cpp"
using namespace std;
class Donate:public Customer{
    protected:
        int money;
    public:
        Donate(){
            cout<<"Enter the money you wanna donate ";
            cin>>money;
            count=getCount("donate");
            string folderName=makeFolder(firstName,lastName,"donate",count);
            storeData(age,money,gender,folderName);
            updateCount("donate",count+1);
        }
        Donate(int id):Customer(id){
            money=getData(this);
            cout<<money;
            cout<<firstName<<lastName<<age<<count<<gender;
        }
        
};
class Report:public Customer{

};
int main(){
    cout<<"Welcome to a pet NGO ";
    int choice;
    cout<<"please ente the choice \n";
    cout<<"1. donate\n";
    cout<<"2. recieve\n";
    cin>>choice;
    if(choice==1){
        Donate d;
    }
    else{
        int id;
        cout<<"enter your id \n";
        cin>>id;
        Donate d(id);
    }
    return 0;
}